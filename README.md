# CEPARCO SIMD Programming Project
**Group Members**
- Hernaez, Raeka Estrelle
- Liwanag, Ram Miguel
- Serrano, Paul Rhazzel
- Tiu, Kyle 
---
## Program Output and Execution Time
The following screenshots show the program outputs and average execution times for all tested vector sizes in both Debug and Release modes

### Debug Program Output
### 2<sup>20</sup>
<img width="510" height="500" alt="image" src="https://github.com/user-attachments/assets/e4824f90-ed5f-4629-a438-3c6f5dd30d8b"/>

### 2<sup>26</sup>
<img width="510" height="500" alt="image" src="https://github.com/user-attachments/assets/333239c2-6d5c-4dd6-a2c9-a0bbe1c71b00" />

### 2<sup>28</sup> (as alternative for 2<sup>30</sup>)
<img width="510" height="500" alt="image" src="https://github.com/user-attachments/assets/9c1ffa74-a40a-4a51-a66d-34ff40b6cce3" />

### Release Program Output
### 2<sup>20</sup>
<img width="510" height="500" alt="image" src="https://github.com/user-attachments/assets/e80e6e0c-9feb-4490-948b-bd2318f8c5bd" />

### 2<sup>26</sup>
<img width="510" height="500" alt="image" src="https://github.com/user-attachments/assets/61b74911-8cd4-43da-94dc-90f81d3b2e13" />

### 2<sup>28</sup> (as alternative for 2<sup>30</sup>)
<img width="510" height="500" alt="image" src="https://github.com/user-attachments/assets/837951a8-565d-48ce-8d9a-9afe38821a81" />

---
## Comparative Table and Performance Analysis
### Debug Results
Each kernel automatically runs 30 times, and the average execution time is recorded below:
| Vector Size | C (ms) | x84-64 (ms) | SIMD XMM (ms) | SIMD YMM (ms) |
|-------------|--------|-------------|---------------|---------------|
| 2<sup>20</sup> | 2.228727 ms | 0.872700 ms | 0.618217 ms | 0.489837 ms |
| 2<sup>26</sup> | 150.110820 ms | 51.171017 ms | 37.480680 ms | 37.028573 ms |
| 2<sup>28</sup> | 589.386130 ms | 244.100700 ms | 145.379133 ms | 139.506310 ms |

### Release Results
Each kernel automatically runs 30 times, and the average execution time is recorded below:
| Vector Size | C (ms) | x84-64 (ms) | SIMD XMM (ms) | SIMD YMM (ms) |
|-------------|--------|-------------|---------------|---------------|
| 2<sup>20</sup> | 0.610970 ms | 0.788550 ms | 0.496523 ms | 0.493613 ms |
| 2<sup>26</sup> | 34.946617 ms | 42.264160 ms | 37.312290 ms | 36.982870 ms |
| 2<sup>28</sup> | 150.827237 ms | 196.881110 ms | 151.298413 ms | 147.800773 ms |

### Analysis

The results show that performance depends on the vector size and build configuration. In Debug mode, the assembly implementations outperformed the C implementation consistently. YMM was approximately 4.2% faster than XMM.

In Release mode, however, the C implementation performed better than any scalar assembly at every tested vector size. Indicating that the compiler’s optimizations can produce more efficient code than a straightforward scalar assembly loop. This successfully shows why it matters to analyze performance both in Debug and Release mode separately.

SIMD improved performance by processing multiple single-precision floating-point values in parallel. XMM registers being 128 bits wide processes four floats per vector instruction, YMM registers being 256 bits wide processes eight floats per vector instruction. It reduces loop overhead, and explains why XMM, especially YMM, is at an advantage with larger vector sizes.

In Release mode, the performance difference between XMM and YMM was small. At 2^28 YMM took 147.8ms, compared with 151.3ms for XMM, making it approximately 1.02x faster. Since the vector triad performs only one multiplication and one addition per element while transferring 16 bytes of data, memory bandwidth may limit performance. Although for computer/computing time, which operates under nano-pico seconds this has a relative difference.

---
## Speedup Comparison

---
## Correctness Check
Correctness checks for all the tested vector sizes are already implemented in the main program and shown in the Program Output and Execution Time Section.
The correctness results below use the Debug results with a vector size of 2<sup>20</sup>

### C
<img width="456" height="92" alt="image" src="https://github.com/user-attachments/assets/9c0b42d8-a04d-416b-8eba-94c462348c35" />

### x86-64
<img width="459" height="86" alt="image" src="https://github.com/user-attachments/assets/980601de-0ab4-460d-8471-e5e534de220e" />

### SIMD XMM register
<img width="456" height="87" alt="image" src="https://github.com/user-attachments/assets/18df5d22-efe4-4997-83f4-ce46d1609be7" />

### SIMD YMM register
<img width="454" height="76" alt="image" src="https://github.com/user-attachments/assets/8df6445b-16df-4e81-9183-19b48cc08ed3"/>

---
## Boundary Check
### (Debug Mode) n = 1,003
<img width="510" height="500" alt="image" src="https://github.com/user-attachments/assets/567034a9-6f29-4053-a94b-50b3ef1abeb7" />

### (Debug Mode) n = 1,000,007
<img width="510" height="500" alt="image" src="https://github.com/user-attachments/assets/b44fe7e1-8907-4fe9-be7c-bfbf9357baa3" />


---
## Overall Results Analysis
The results show that the fastest implementation depends on the build configuration and vector size. In Debug mode, YMM achieved the lowest execution time for all three vector sizes, reaching a speedup of approximately 4.22× over C at 2^28. Its 256-bit registers process eight single-precision floats per vector instruction, compared with four floats for 128-bit XMM registers, reducing loop iterations and improving throughput.

In Release mode, the optimized C implementation outperformed scalar assembly at every tested size. XMM and YMM performed better than C at 2^20, but both were slightly slower at 2^26. At 2^28, YMM achieved the lowest execution time at 147.80 ms, approximately 1.02× faster than C at 150.83 ms and XMM at 151.30 ms. This shows that compiler optimization can make C highly efficient and that wider SIMD registers do not guarantee proportional speedups.

The small performance difference between XMM and YMM for larger vectors suggests that memory bandwidth may limit the benefit of additional SIMD width. The vector triad performs one multiplication and one addition per element while transferring 16 bytes of data. Consequently, performance depends not only on the number of elements processed per instruction but also on memory behavior, loop overhead, and compiler optimization.

Overall, YMM provided the best measured performance for the largest vector size, while optimized C remained competitive in Release mode. The results demonstrate the importance of evaluating both Debug and Release builds and comparing actual execution times rather than assuming that hand-written assembly or wider SIMD registers will always be faster.

---
## Implementation Discussion
The primary roadblock that the group encountered was handling the tail portion of vector sizes that were not divisible by 4 or 8, as this directly affected the XMM and YMM versions of the kernel. To this end, the group’s major AHA! moment was when the realization was made that by using logic AND, the group is able to round down a provided number to its nearest multiple of 4 and 8 for the XMM and YMM implementations respectively. As such, these two kernels were specially modified in a way that has a main loop complete the vector computations in groups of 4 and 8 bytes first, then has a smaller loop that occurs after the main loop that handles the stragglers. As an example, if the vector size was set to 1003, the first 1000 indexes are completed in the main loop while the last 3 indexes are handled by the smaller loop.  
