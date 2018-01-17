/* ======================================================================== *
 * IMGLIB -- TI Image and Video Processing Library                          *
 *                                                                          *
 *                                                                          *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/   *
 *                                                                          *
 *                                                                          *
 *  Redistribution and use in source and binary forms, with or without      *
 *  modification, are permitted provided that the following conditions      *
 *  are met:                                                                *
 *                                                                          *
 *    Redistributions of source code must retain the above copyright        *
 *    notice, this list of conditions and the following disclaimer.         *
 *                                                                          *
 *    Redistributions in binary form must reproduce the above copyright     *
 *    notice, this list of conditions and the following disclaimer in the   *
 *    documentation and/or other materials provided with the                *
 *    distribution.                                                         *
 *                                                                          *
 *    Neither the name of Texas Instruments Incorporated nor the names of   *
 *    its contributors may be used to endorse or promote products derived   *
 *    from this software without specific prior written permission.         *
 *                                                                          *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 * ======================================================================== */

#ifndef IMG_SOBEL_7x7_16s_H_
#define IMG_SOBEL_7x7_16s_H_ 1
                                                                     
/** @defgroup IMG_sobel_7x7_16s */
/** @ingroup  IMG_sobel_7x7_16s */
/* @{ */

/**
 * @par Description:
 *  This function applies 7-by-7 horizontal and vertical Sobel edge detection 
 *  masks to the input image and produces an output image which is six rows 
 *  shorter than the input image.  Within each row of the output, the first 
 *  three and the last three pixels will not contain meaningful results.
 * @par 
 *    @param in       Input image pointer
 *    @param out      Output image pointer
 *    @param cols     Number of columns in the image
 *    @param rows     Number of rows in the image
 *
 *
 * @par Algorithm:
 *  The Sobel edge-detection masks shown below are applied to the input image 
 *  independently.  The absolute value of each mask result are summed together
 *  and saturated to 16-bits. 
 *
 * @verbatim

          Horizontal Mask:                                                     
              -1 -1 -1 -2 -1 -1 -1
              -1 -1 -1 -2 -1 -1 -1
              -1 -1 -1 -2 -1 -1 -1
               0  0  0  0  0  0  0
               1  1  1  2  1  1  1
               1  1  1  2  1  1  1
               1  1  1  2  1  1  1

          Vertical Mask:                                                       
              -1 -1 -1  0  1  1  1
              -1 -1 -1  0  1  1  1
              -1 -1 -1  0  1  1  1
              -2 -2 -2  0  2  2  2
              -1 -1 -1  0  1  1  1
              -1 -1 -1  0  1  1  1
              -1 -1 -1  0  1  1  1
   @endverbatim
 * 
 * @par 
 *  The example below illustrates how the implementation would operate on a 
 *  given input image. Imagine the following 10-by-16 pixel input image:
 *
 * @verbatim

              yyyyyyyyyyyyyyyy
              yyyyyyyyyyyyyyyy
              yyyyyyyyyyyyyyyy
              yyyxxxxxxxxxxyyy
              yyyxxxxxxxxxxyyy
              yyyxxxxxxxxxxyyy
              yyyxxxxxxxxxxyyy
              yyyyyyyyyyyyyyyy
              yyyyyyyyyyyyyyyy
              yyyyyyyyyyyyyyyy
   @endverbatim
 * @par 
 *  Where the output is only defined for the inner pixels, x, due to the edge 
 *  effect of the 7-by-7 pixel mask.
 * @par 
 *  The output image would have the form:                                         
 * @verbatim
                                                                          
              tttXXXXXXXXXXzzz
              zzzXXXXXXXXXXzzz
              zzzXXXXXXXXXXzzz
              zzzXXXXXXXXXXttt

  Where:   X = sobel(x)   The algorithm is applied to that pixel. The correct 
                          output is obtained, the data surrounding the pixel 
                          is used            
                                                                      
           t              Data in the output buffer in that position is unaltered
                                                                         
           z = sobel(y)   The algorithm is applied to that pixel. The output is 
                          not meaningful since the data necessary to process the 
                          pixel is not available.                         
  @endverbatim
 * @par 
 *  This means that (rows-6) lines of pixels will be processed.  Though all 
 *  pixels within each line are processed, the results for the first three and 
 *  last three pixels are not valid, yet still provided.  This makes the control 
 *  code simpler and saves cycles.  Note that The first three pixels in the first 
 *  processed row and the last three pixels in the last processed row are not 
 *  generated.    
 * @par 
 *  The natural C implementation has no restrictions. The optimized intrinsic 
 *  C code has restrictions as noted in Assumptions below.    
 *
 *
 * @par Assumptions:
 *    - The input array and output array should not overlap  
 *    - Both input and output arrays must be 16-bit aligned
 *    - The "cols" input value must be greater than 7 and a multiple of 2
 *    - The "rows" input value must be greater than or equal to 7
 *    - The value (cols * (rows - 6) - 6) must be at least 2
 *
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C64x+ processors
 *    - The values of the three left-most and three right-most pixels on 
 *      each output line are not defined
 *
 *
 * @par Benchmarks:
 *  See IMGLIB_Test_Report.html for cycle and memory information.
 *
 */

void IMG_sobel_7x7_16s
(
    const short *restrict  in,   /* Input image data   */
          short *restrict out,   /* Output image data  */
          short          cols,   /* image columns      */
          short          rows    /* Image rows         */
);

/** @} */

#endif

/* ======================================================================== */
/*  End of file:  IMG_sobel_7x7_16s.h                                       */
/* ======================================================================== */
