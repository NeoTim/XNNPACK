// Auto-generated file. Do not edit!
//   Template: src/f32-sigmoid/avx-p5.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <immintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/vunary.h>


static const int32_t mask_table[14] = {-1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0};

void xnn_f32_sigmoid_ukernel__avx_rr2_p5_nr1fma_x16(
    size_t n,
    const float* x,
    float* y,
    const void* params)
{
  assert(n % sizeof(float) == 0);

  const __m256 vsign_mask = _mm256_set1_ps(-0.0f);
  const __m256 vmagic_bias = _mm256_set1_ps(0x1.8000FEp23f);
  const __m256 vlog2e = _mm256_set1_ps(0x1.715476p0f);
  const __m256 vminus_ln2_hi = _mm256_set1_ps(-0x1.62E43p-1f);
  const __m256 vminus_ln2_lo = _mm256_set1_ps(0x1.05C61p-29f);
  const __m256 vc5 = _mm256_set1_ps(0x1.0F9F9Cp-7f);
  const __m256 vc4 = _mm256_set1_ps(0x1.573A1Ap-5f);
  const __m256 vc3 = _mm256_set1_ps(0x1.555A80p-3f);
  const __m256 vc2 = _mm256_set1_ps(0x1.FFFDC6p-2f);
  const __m256 vc1 = _mm256_set1_ps(0x1.FFFFF6p-1f);
  const __m256 vone = _mm256_set1_ps(1.0f);
  const __m256 vdenorm_cutoff = _mm256_set1_ps(-0x1.5D589Ep+6f);

  for (; n >= 16 * sizeof(float); n -= 16 * sizeof(float)) {
    const __m256 vx0 = _mm256_loadu_ps(x);
    const __m256 vx1 = _mm256_loadu_ps(x + 8);
    x += 16;

    const __m256 vz0 = _mm256_or_ps(vx0, vsign_mask);
    const __m256 vz1 = _mm256_or_ps(vx1, vsign_mask);

    __m256 vn0 = _mm256_add_ps(_mm256_mul_ps(vz0, vlog2e), vmagic_bias);
    __m256 vn1 = _mm256_add_ps(_mm256_mul_ps(vz1, vlog2e), vmagic_bias);

    __m128 lo, hi;
    lo = _mm256_extractf128_ps(vn0, 0);
    hi = _mm256_extractf128_ps(vn0, 1);
    lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(lo), 23));
    hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(hi), 23));
    const __m256 vs0 = _mm256_set_m128(hi, lo);
    lo = _mm256_extractf128_ps(vn1, 0);
    hi = _mm256_extractf128_ps(vn1, 1);
    lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(lo), 23));
    hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(hi), 23));
    const __m256 vs1 = _mm256_set_m128(hi, lo);

    vn0 = _mm256_sub_ps(vn0, vmagic_bias);
    vn1 = _mm256_sub_ps(vn1, vmagic_bias);

    __m256 vt0 = _mm256_add_ps(_mm256_mul_ps(vn0, vminus_ln2_hi), vz0);
    __m256 vt1 = _mm256_add_ps(_mm256_mul_ps(vn1, vminus_ln2_hi), vz1);

    vt0 = _mm256_add_ps(_mm256_mul_ps(vn0, vminus_ln2_lo), vt0);
    vt1 = _mm256_add_ps(_mm256_mul_ps(vn1, vminus_ln2_lo), vt1);

    __m256 vp0 = _mm256_add_ps(_mm256_mul_ps(vc5, vt0), vc4);
    __m256 vp1 = _mm256_add_ps(_mm256_mul_ps(vc5, vt1), vc4);

    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc3);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc3);

    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc2);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc2);

    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc1);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc1);

    vt0 = _mm256_mul_ps(vt0, vs0);
    vt1 = _mm256_mul_ps(vt1, vs1);

    const __m256 ve0 = _mm256_add_ps(_mm256_mul_ps(vt0, vp0), vs0);
    const __m256 ve1 = _mm256_add_ps(_mm256_mul_ps(vt1, vp1), vs1);

    const __m256 vd0 = _mm256_add_ps(ve0, vone);
    const __m256 vd1 = _mm256_add_ps(ve1, vone);

    __m256 vr0 = _mm256_rcp_ps(vd0);
    __m256 vr1 = _mm256_rcp_ps(vd1);

    __m256 tmp, tmp2;
    tmp = _mm256_mul_ps(vr0, vd0);
    tmp2 = _mm256_sub_ps(vone, tmp);
    vr0 = _mm256_add_ps(_mm256_mul_ps(tmp2, vr0), vr0);
    tmp = _mm256_mul_ps(vr1, vd1);
    tmp2 = _mm256_sub_ps(vone, tmp);
    vr1 = _mm256_add_ps(_mm256_mul_ps(tmp2, vr1), vr1);


    __m256 vf0 = _mm256_mul_ps(ve0, vr0);
    __m256 vf1 = _mm256_mul_ps(ve1, vr1);

    vf0 = _mm256_andnot_ps(_mm256_cmp_ps(vz0, vdenorm_cutoff, _CMP_LT_OS), vf0);
    vf1 = _mm256_andnot_ps(_mm256_cmp_ps(vz1, vdenorm_cutoff, _CMP_LT_OS), vf1);

    vf0 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf0), vf0, vx0);
    vf1 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf1), vf1, vx1);

    _mm256_storeu_ps(y, vf0);
    _mm256_storeu_ps(y + 8, vf1);
    y += 16;
  }
  for (; n >= 8 * sizeof(float); n -= 8 * sizeof(float)) {
    const __m256 vx = _mm256_loadu_ps(x);
    x += 8;

    const __m256 vz = _mm256_or_ps(vx, vsign_mask);

    __m256 vn = _mm256_add_ps(_mm256_mul_ps(vz, vlog2e), vmagic_bias);
    __m128 lo = _mm256_extractf128_ps(vn, 0);
    __m128 hi = _mm256_extractf128_ps(vn, 1);
    lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(lo), 23));
    hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(hi), 23));
    const __m256 vs = _mm256_set_m128(hi, lo);
    vn = _mm256_sub_ps(vn, vmagic_bias);

    __m256 vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_hi), vz);
    vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_lo), vt);

    __m256 vp = _mm256_add_ps(_mm256_mul_ps(vc5, vt), vc4);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc3);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc2);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc1);

    vt = _mm256_mul_ps(vt, vs);
    const __m256 ve = _mm256_add_ps(_mm256_mul_ps(vt, vp), vs);

    const __m256 vd = _mm256_add_ps(ve, vone);
    __m256 vr = _mm256_rcp_ps(vd);
    __m256 tmp = _mm256_mul_ps(vr, vd);
    __m256 tmp2 = _mm256_sub_ps(vone, tmp);
    vr = _mm256_add_ps(_mm256_mul_ps(tmp2, vr), vr);
    __m256 vf = _mm256_mul_ps(ve, vr);

    vf = _mm256_andnot_ps(_mm256_cmp_ps(vz, vdenorm_cutoff, _CMP_LT_OS), vf);
    vf = _mm256_blendv_ps(_mm256_sub_ps(vone, vf), vf, vx);

    _mm256_storeu_ps(y, vf);
    y += 8;
  }
  if XNN_UNLIKELY(n != 0) {
    assert(n >= 1 * sizeof(float));
    assert(n <= 7 * sizeof(float));
    __m256i vmask = _mm256_loadu_si256((const __m256i*) ((uintptr_t) &mask_table[7] - n));

    const __m256 vx = _mm256_maskload_ps(x, vmask);

    const __m256 vz = _mm256_or_ps(vx, vsign_mask);

    __m256 vn = _mm256_add_ps(_mm256_mul_ps(vz, vlog2e), vmagic_bias);
    __m128 lo = _mm256_extractf128_ps(vn, 0);
    __m128 hi = _mm256_extractf128_ps(vn, 1);
    lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(lo), 23));
    hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(hi), 23));
    const __m256 vs = _mm256_set_m128(hi, lo);
    vn = _mm256_sub_ps(vn, vmagic_bias);

    __m256 vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_hi), vz);
    vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_lo), vt);

    __m256 vp = _mm256_add_ps(_mm256_mul_ps(vc5, vt), vc4);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc3);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc2);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc1);

    vt = _mm256_mul_ps(vt, vs);
    const __m256 ve = _mm256_add_ps(_mm256_mul_ps(vt, vp), vs);

    const __m256 vd = _mm256_add_ps(ve, vone);
    __m256 vr = _mm256_rcp_ps(vd);
    __m256 tmp = _mm256_mul_ps(vr, vd);
    __m256 tmp2 = _mm256_sub_ps(vone, tmp);
    vr = _mm256_add_ps(_mm256_mul_ps(tmp2, vr), vr);
    __m256 vf = _mm256_mul_ps(ve, vr);

    vf = _mm256_andnot_ps(_mm256_cmp_ps(vz, vdenorm_cutoff, _CMP_LT_OS), vf);
    vf = _mm256_blendv_ps(_mm256_sub_ps(vone, vf), vf, vx);

    // _mm256_maskstore_ps(y, vmask, vf) could be used here, but triggers msan failures (probably an msan bug).
    __m128 vf_lo = _mm256_castps256_ps128(vf);
    if (n & (4 * sizeof(float))) {
      _mm_storeu_ps(y, vf_lo);
      vf_lo = _mm256_extractf128_ps(vf, 1);
      y += 4;
    }
    if (n & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) y, vf_lo);
      vf_lo = _mm_movehl_ps(vf_lo, vf_lo);
      y += 2;
    }
    if (n & (1 * sizeof(float))) {
      _mm_store_ss(y, vf_lo);
    }
  }
}
