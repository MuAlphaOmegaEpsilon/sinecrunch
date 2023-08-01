#pragma once
#include<stdint.h>

// 32bit unitary angle.
struct ungle_t
{
	constexpr ungle_t()noexcept:value(0){}
	constexpr ungle_t(ungle_t u)noexcept:value(u.value){}
	constexpr ungle_t(uint32_t u)noexcept:value(static_cast<uint32_t>((1UL<<32UL)*(u%360)/360)){}
	constexpr ungle_t(int32_t i)noexcept:value(){}
	constexpr ungle_t(float f)noexcept:value(){}
	uint32_t value;
};