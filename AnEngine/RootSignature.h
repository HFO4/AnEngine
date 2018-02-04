#pragma once
#ifndef __ROOTSIGNATURE_H__
#define __ROOTSIGNATURE_H__

#include"DX.h"

namespace AnEngine::RenderCore
{
	class RootParameter
	{
	public:
		RootParameter() = default;
		~RootParameter() = default;

		void Clear();
	};

	class RootSignature
	{
	protected:
		ComPtr<ID3D12RootSignature> m_rootSignature;

	public:
		RootSignature() = default;
		~RootSignature() = default;
		void Reset();

		ID3D12RootSignature* GetRootSignature() const;
	};
}

#endif // !__ROOTSIGNATURE_H__