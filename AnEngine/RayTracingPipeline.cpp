#include "RayTracingPipeline.h"
#include "GraphicsCard.h"
#include "RenderCoreConstants.h"
#include "../Assets/CompiledShaders/Raytracing.hlsl.h"

namespace AnEngine::RenderCore
{
	void RayTracingPipeline::Initialize()
	{
		// ����7����ϳ�RTPSO���Ӷ���
		// �Ӷ�����Ҫͨ��Ĭ�ϻ���ʽ������DXIL����������ɫ�����������
		// Ĭ�Ϲ���������û���κ�����������κ���ͬ���͵��Ӷ����ÿ����������ɫ����ڵ㡣
		// ����򵥵�ʾ��ʹ�ó����ظ�ǩ���Ӷ���֮���Ĭ����ɫ���������д���������ʾĿ�ĵ���ȷ������
		// 1 * DXIL��
		// 1 * ���������
		// 1 * ��ɫ������
		// 2 * ���ظ�ǩ���͹���
		// 1 * ȫ�ָ�ǩ��
		// 1 * �ܵ�����

		const wchar_t* hitGroupName = L"MyHitGroup";
		const wchar_t* raygenShaderName = L"MyRaygenShader";
		const wchar_t* closestHitShaderName = L"MyClosestHitShader";
		const wchar_t* missShaderName = L"MyMissShader";

		CD3D12_STATE_OBJECT_DESC raytracingPipeline{ D3D12_STATE_OBJECT_TYPE_RAYTRACING_PIPELINE };


		// DXIL��
		// ����״̬�������ɫ��������ڵ㡣������ɫ��������Ϊ�Ӷ��������Ҫͨ��DXIL���Ӷ��󴫵����ǡ�
		var lib = raytracingPipeline.CreateSubobject<CD3D12_DXIL_LIBRARY_SUBOBJECT>();
		D3D12_SHADER_BYTECODE libdxil = CD3DX12_SHADER_BYTECODE((void *)g_pRaytracing, ARRAYSIZE(g_pRaytracing));
		lib->SetDXILLibrary(&libdxil);

		//����ӿ��н��ĸ���ɫ�����������档
		//���û��ΪDXIL���Ӷ�������ɫ����������������ɫ����������ˮ�档
		//�����ʾ���У�Ϊ�˷������������ʡ�����ʾ������Ϊʾ��ʹ�ÿ��е�������ɫ����
		{
			lib->DefineExport(raygenShaderName);
			lib->DefineExport(closestHitShaderName);
			lib->DefineExport(missShaderName);
		}

		// Triangle hit group
		// A hit group specifies closest hit, any hit and intersection shaders to be executed when a ray intersects the geometry's triangle/AABB.
		// In this sample, we only use triangle geometry with a closest hit shader, so others are not set.
		auto hitGroup = raytracingPipeline.CreateSubobject<CD3D12_HIT_GROUP_SUBOBJECT>();
		hitGroup->SetClosestHitShaderImport(closestHitShaderName);
		hitGroup->SetHitGroupExport(hitGroupName);

		// Shader config
		// Defines the maximum sizes in bytes for the ray payload and attribute structure.
		auto shaderConfig = raytracingPipeline.CreateSubobject<CD3D12_RAYTRACING_SHADER_CONFIG_SUBOBJECT>();
		UINT payloadSize = 4 * sizeof(float);   // float4 color
		UINT attributeSize = 2 * sizeof(float); // float2 barycentrics
		shaderConfig->Config(payloadSize, attributeSize);

		// Local root signature and shader association
		//CreateLocalRootSignatureSubobjects(&raytracingPipeline);
		// This is a root signature that enables a shader to have unique arguments that come from shader tables.

		// Global root signature
		// This is a root signature that is shared across all raytracing shaders invoked during a DispatchRays() call.
		auto globalRootSignature = raytracingPipeline.CreateSubobject<CD3D12_ROOT_SIGNATURE_SUBOBJECT>();
		//globalRootSignature->SetRootSignature(m_raytracingGlobalRootSignature.Get());

		// Pipeline config
		// Defines the maximum TraceRay() recursion depth.
		auto pipelineConfig = raytracingPipeline.CreateSubobject<CD3D12_RAYTRACING_PIPELINE_CONFIG_SUBOBJECT>();
		// PERFOMANCE TIP: Set max recursion depth as low as needed 
		// as drivers may apply optimization strategies for low recursion depths. 
		UINT maxRecursionDepth = 1; // ~ primary rays only. 
		pipelineConfig->Config(maxRecursionDepth);

#if _DEBUG
		PrintStateObjectDesc(raytracingPipeline);
#endif

		// Create the state object.
		/*if (r_raytracingAPI == RaytracingAPI::FallbackLayer)
		{
			ThrowIfFailed(r_fallbackDevice->CreateStateObject(raytracingPipeline, IID_PPV_ARGS(&m_fallbackStateObject)), L"Couldn't create DirectX Raytracing state object.\n");
		}
		else // DirectX Raytracing
		{
			ThrowIfFailed(r_dxrDevice->CreateStateObject(raytracingPipeline, IID_PPV_ARGS(&m_dxrStateObject)), L"Couldn't create DirectX Raytracing state object.\n");
		}*/
	}
}