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

void xnn_f32_sigmoid_ukernel__avx_rr2_p5_div_x48(
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

  for (; n >= 48 * sizeof(float); n -= 48 * sizeof(float)) {
    const __m256 vx0 = _mm256_loadu_ps(x);
    const __m256 vx1 = _mm256_loadu_ps(x + 8);
    const __m256 vx2 = _mm256_loadu_ps(x + 16);
    const __m256 vx3 = _mm256_loadu_ps(x + 24);
    const __m256 vx4 = _mm256_loadu_ps(x + 32);
    const __m256 vx5 = _mm256_loadu_ps(x + 40);
    x += 48;

    const __m256 vz0 = _mm256_or_ps(vx0, vsign_mask);
    const __m256 vz1 = _mm256_or_ps(vx1, vsign_mask);
    const __m256 vz2 = _mm256_or_ps(vx2, vsign_mask);
    const __m256 vz3 = _mm256_or_ps(vx3, vsign_mask);
    const __m256 vz4 = _mm256_or_ps(vx4, vsign_mask);
    const __m256 vz5 = _mm256_or_ps(vx5, vsign_mask);

    __m256 vn0 = _mm256_add_ps(_mm256_mul_ps(vz0, vlog2e), vmagic_bias);
    __m256 vn1 = _mm256_add_ps(_mm256_mul_ps(vz1, vlog2e), vmagic_bias);
    __m256 vn2 = _mm256_add_ps(_mm256_mul_ps(vz2, vlog2e), vmagic_bias);
    __m256 vn3 = _mm256_add_ps(_mm256_mul_ps(vz3, vlog2e), vmagic_bias);
    __m256 vn4 = _mm256_add_ps(_mm256_mul_ps(vz4, vlog2e), vmagic_bias);
    __m256 vn5 = _mm256_add_ps(_mm256_mul_ps(vz5, vlog2e), vmagic_bias);

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
    lo = _mm256_extractf128_ps(vn2, 0);
    hi = _mm256_extractf128_ps(vn2, 1);
    lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(lo), 23));
    hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(hi), 23));
    const __m256 vs2 = _mm256_set_m128(hi, lo);
    lo = _mm256_extractf128_ps(vn3, 0);
    hi = _mm256_extractf128_ps(vn3, 1);
    lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(lo), 23));
    hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(hi), 23));
    const __m256 vs3 = _mm256_set_m128(hi, lo);
    lo = _mm256_extractf128_ps(vn4, 0);
    hi = _mm256_extractf128_ps(vn4, 1);
    lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(lo), 23));
    hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(hi), 23));
    const __m256 vs4 = _mm256_set_m128(hi, lo);
    lo = _mm256_extractf128_ps(vn5, 0);
    hi = _mm256_extractf128_ps(vn5, 1);
    lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(lo), 23));
    hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(hi), 23));
    const __m256 vs5 = _mm256_set_m128(hi, lo);

    vn0 = _mm256_sub_ps(vn0, vmagic_bias);
    vn1 = _mm256_sub_ps(vn1, vmagic_bias);
    vn2 = _mm256_sub_ps(vn2, vmagic_bias);
    vn3 = _mm256_sub_ps(vn3, vmagic_bias);
    vn4 = _mm256_sub_ps(vn4, vmagic_bias);
    vn5 = _mm256_sub_ps(vn5, vmagic_bias);

    __m256 vt0 = _mm256_add_ps(_mm256_mul_ps(vn0, vminus_ln2_hi), vz0);
    __m256 vt1 = _mm256_add_ps(_mm256_mul_ps(vn1, vminus_ln2_hi), vz1);
    __m256 vt2 = _mm256_add_ps(_mm256_mul_ps(vn2, vminus_ln2_hi), vz2);
    __m256 vt3 = _mm256_add_ps(_mm256_mul_ps(vn3, vminus_ln2_hi), vz3);
    __m256 vt4 = _mm256_add_ps(_mm256_mul_ps(vn4, vminus_ln2_hi), vz4);
    __m256 vt5 = _mm256_add_ps(_mm256_mul_ps(vn5, vminus_ln2_hi), vz5);

    vt0 = _mm256_add_ps(_mm256_mul_ps(vn0, vminus_ln2_lo), vt0);
    vt1 = _mm256_add_ps(_mm256_mul_ps(vn1, vminus_ln2_lo), vt1);
    vt2 = _mm256_add_ps(_mm256_mul_ps(vn2, vminus_ln2_lo), vt2);
    vt3 = _mm256_add_ps(_mm256_mul_ps(vn3, vminus_ln2_lo), vt3);
    vt4 = _mm256_add_ps(_mm256_mul_ps(vn4, vminus_ln2_lo), vt4);
    vt5 = _mm256_add_ps(_mm256_mul_ps(vn5, vminus_ln2_lo), vt5);

    __m256 vp0 = _mm256_add_ps(_mm256_mul_ps(vc5, vt0), vc4);
    __m256 vp1 = _mm256_add_ps(_mm256_mul_ps(vc5, vt1), vc4);
    __m256 vp2 = _mm256_add_ps(_mm256_mul_ps(vc5, vt2), vc4);
    __m256 vp3 = _mm256_add_ps(_mm256_mul_ps(vc5, vt3), vc4);
    __m256 vp4 = _mm256_add_ps(_mm256_mul_ps(vc5, vt4), vc4);
    __m256 vp5 = _mm256_add_ps(_mm256_mul_ps(vc5, vt5), vc4);

    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc3);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc3);
    vp2 = _mm256_add_ps(_mm256_mul_ps(vp2, vt2), vc3);
    vp3 = _mm256_add_ps(_mm256_mul_ps(vp3, vt3), vc3);
    vp4 = _mm256_add_ps(_mm256_mul_ps(vp4, vt4), vc3);
    vp5 = _mm256_add_ps(_mm256_mul_ps(vp5, vt5), vc3);

    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc2);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc2);
    vp2 = _mm256_add_ps(_mm256_mul_ps(vp2, vt2), vc2);
    vp3 = _mm256_add_ps(_mm256_mul_ps(vp3, vt3), vc2);
    vp4 = _mm256_add_ps(_mm256_mul_ps(vp4, vt4), vc2);
    vp5 = _mm256_add_ps(_mm256_mul_ps(vp5, vt5), vc2);

    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc1);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc1);
    vp2 = _mm256_add_ps(_mm256_mul_ps(vp2, vt2), vc1);
    vp3 = _mm256_add_ps(_mm256_mul_ps(vp3, vt3), vc1);
    vp4 = _mm256_add_ps(_mm256_mul_ps(vp4, vt4), vc1);
    vp5 = _mm256_add_ps(_mm256_mul_ps(vp5, vt5), vc1);

    vt0 = _mm256_mul_ps(vt0, vs0);
    vt1 = _mm256_mul_ps(vt1, vs1);
    vt2 = _mm256_mul_ps(vt2, vs2);
    vt3 = _mm256_mul_ps(vt3, vs3);
    vt4 = _mm256_mul_ps(vt4, vs4);
    vt5 = _mm256_mul_ps(vt5, vs5);

    const __m256 ve0 = _mm256_add_ps(_mm256_mul_ps(vt0, vp0), vs0);
    const __m256 ve1 = _mm256_add_ps(_mm256_mul_ps(vt1, vp1), vs1);
    const __m256 ve2 = _mm256_add_ps(_mm256_mul_ps(vt2, vp2), vs2);
    const __m256 ve3 = _mm256_add_ps(_mm256_mul_ps(vt3, vp3), vs3);
    const __m256 ve4 = _mm256_add_ps(_mm256_mul_ps(vt4, vp4), vs4);
    const __m256 ve5 = _mm256_add_ps(_mm256_mul_ps(vt5, vp5), vs5);

    const __m256 vd0 = _mm256_add_ps(ve0, vone);
    const __m256 vd1 = _mm256_add_ps(ve1, vone);
    const __m256 vd2 = _mm256_add_ps(ve2, vone);
    const __m256 vd3 = _mm256_add_ps(ve3, vone);
    const __m256 vd4 = _mm256_add_ps(ve4, vone);
    const __m256 vd5 = _mm256_add_ps(ve5, vone);

    __m256 vf0 = _mm256_div_ps(ve0, vd0);
    __m256 vf1 = _mm256_div_ps(ve1, vd1);
    __m256 vf2 = _mm256_div_ps(ve2, vd2);
    __m256 vf3 = _mm256_div_ps(ve3, vd3);
    __m256 vf4 = _mm256_div_ps(ve4, vd4);
    __m256 vf5 = _mm256_div_ps(ve5, vd5);

    vf0 = _mm256_andnot_ps(_mm256_cmp_ps(vz0, vdenorm_cutoff, _CMP_LT_OS), vf0);
    vf1 = _mm256_andnot_ps(_mm256_cmp_ps(vz1, vdenorm_cutoff, _CMP_LT_OS), vf1);
    vf2 = _mm256_andnot_ps(_mm256_cmp_ps(vz2, vdenorm_cutoff, _CMP_LT_OS), vf2);
    vf3 = _mm256_andnot_ps(_mm256_cmp_ps(vz3, vdenorm_cutoff, _CMP_LT_OS), vf3);
    vf4 = _mm256_andnot_ps(_mm256_cmp_ps(vz4, vdenorm_cutoff, _CMP_LT_OS), vf4);
    vf5 = _mm256_andnot_ps(_mm256_cmp_ps(vz5, vdenorm_cutoff, _CMP_LT_OS), vf5);

    vf0 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf0), vf0, vx0);
    vf1 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf1), vf1, vx1);
    vf2 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf2), vf2, vx2);
    vf3 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf3), vf3, vx3);
    vf4 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf4), vf4, vx4);
    vf5 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf5), vf5, vx5);

    _mm256_storeu_ps(y, vf0);
    _mm256_storeu_ps(y + 8, vf1);
    _mm256_storeu_ps(y + 16, vf2);
    _mm256_storeu_ps(y + 24, vf3);
    _mm256_storeu_ps(y + 32, vf4);
    _mm256_storeu_ps(y + 40, vf5);
    y += 48;
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
    __m256 vf = _mm256_div_ps(ve, vd);

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
    __m256 vf = _mm256_div_ps(ve, vd);

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
