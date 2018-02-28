#include "ShaderClass.h"
using namespace std;

namespace AnEngine::RenderCore
{
	Shader::Shader(const wstring& fileName, const string& invokeFunction, string&& shaderVersion)
	{
#if defined _DEBUG || defined DEBUG
		m_compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		m_compileFlag = 0;
#endif // _DEBUG || DEBUG

		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(fileName).c_str(), nullptr, nullptr,
			invokeFunction.c_str(), shaderVersion.c_str(), m_compileFlag, 0, &m_blob, nullptr));
	}

	Shader::Shader(wstring&& fileName, string&& invokeFunction, string&& shaderVersion)
	{
#if defined _DEBUG || defined DEBUG
		m_compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		m_compileFlag = 0;
#endif // _DEBUG || DEBUG

		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(fileName).c_str(), nullptr, nullptr,
			invokeFunction.c_str(), shaderVersion.c_str(), m_compileFlag, 0, &m_blob, nullptr));
	}

	D3D12_SHADER_BYTECODE Shader::GetByteCode()
	{
		return std::move(CD3DX12_SHADER_BYTECODE(m_blob.Get()));
	}

	VertexShader::VertexShader(const wstring& fileName) : Shader(fileName, "VSMain", "vs_5_0")
	{
	}

	VertexShader::VertexShader(std::wstring&& fileName) : Shader(fileName, "VSMain", "vs_5_0")
	{
	}

	VertexShader::VertexShader(const wstring& fileName, const string& invokeFunction) :
		Shader(fileName, invokeFunction, "vs_5_0")
	{
	}

	VertexShader::VertexShader(std::wstring&& fileName, std::string && invokeFunction) :
		Shader(fileName, invokeFunction, "vs_5_0")
	{
	}

	PixelShader::PixelShader(const wstring& fileName) : Shader(fileName, "PSMain", "ps_5_0")
	{
	}

	PixelShader::PixelShader(std::wstring && fileName) : Shader(fileName, "PSMain", "ps_5_0")
	{
	}

	PixelShader::PixelShader(const wstring& fileName, const string& invokeFunction) :
		Shader(fileName, invokeFunction, "ps_5_0")
	{
	}

	PixelShader::PixelShader(std::wstring && fileName, std::string && invokeFunction) :
		Shader(fileName, invokeFunction, "ps_5_0")
	{
	}

	/*void VertexShader::CompileFromFile(string& fileName)
	{
		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(ToLPCWSTR(fileName)).c_str(), nullptr, nullptr, "VSMain", "vs_5_0", m_compileFlag, 0, &m_blob, nullptr));
	}

	void PixelShader::CompileFromFile(string& fileName)
	{
		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(ToLPCWSTR(fileName)).c_str(), nullptr, nullptr, "PSMain", "ps_5_0", m_compileFlag, 0, &m_blob, nullptr));
	}

	void GeometryShader::CompileFromFile(string& fileName)
	{
		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(ToLPCWSTR(fileName)).c_str(), nullptr, nullptr, "GSMain", "gs_5_0", m_compileFlag, 0, &m_blob, nullptr));
	}

	void ComputeShader::CompileFromFile(string& fileName)
	{
		ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(ToLPCWSTR(fileName)).c_str(), nullptr, nullptr, "CSMain", "cs_5_0", m_compileFlag, 0, &m_blob, nullptr));
	}*/
}