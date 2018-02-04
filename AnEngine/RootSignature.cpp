#include "RootSignature.h"

namespace AnEngine::RenderCore
{
	void RootSignature::Reset()
	{
	}

	ID3D12RootSignature * RootSignature::GetRootSignature() const
	{
		return m_rootSignature.Get();
	}
}