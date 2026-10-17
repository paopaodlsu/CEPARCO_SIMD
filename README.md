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

The results show that performance depends on the vector size and build configuration. In Debug mode, the assembly implementations outperformed the C implementation consistently. YMM also outperformed XMM by approximately 4%.

In Release mode, however, the C implementation performed better than any scalar assembly at every tested vector size. Indicating that the compiler’s optimizations can produce more efficient code than a straightforward scalar assembly loop. This successfully shows why it matters to analyze performance both in Debug and Release mode separately.

SIMD improved performance by processing multiple single-precision floating-point values in parallel. XMM registers being 128 bits wide processes four floats per vector instruction, YMM registers being 256 bits wide processes eight floats per vector instruction. It reduces loop overhead, and explains why XMM, especially YMM, is at an advantage with larger vector sizes.

In Release mode, the performance difference between XMM and YMM was small. At 2^28 YMM took 147.8ms, compared with 151.3ms for XMM, making it approximately 1.02x faster. Since the vector triad performs only one multiplication and one addition per element while transferring 16 bytes of data, memory bandwidth may limit performance. Although for computer/computing time, which operates under nano-pico seconds this has a relative difference.

---
## Correctness Check
The correctness results below use the Debug results with a vector size of 2<sup>20</sup>

### C
<img width="456" height="92" alt="image" src="https://github.com/user-attachments/assets/9c0b42d8-a04d-416b-8eba-94c462348c35" />

### x86-64
<img width="459" height="86" alt="image" src="https://github.com/user-attachments/assets/980601de-0ab4-460d-8471-e5e534de220e" />

### SIMD XMM register
<img width="456" height="87" alt="image" src="https://github.com/user-attachments/assets/18df5d22-efe4-4997-83f4-ce46d1609be7" />

### SIMD YMM register
<img width="454" height="76" alt="image" src="https://github.com/user-attachments/assets/8df6445b-16df-4e81-9183-19b48cc08ed3" />

Correctness checks for all tested vector sizes are already implemented in the main program and shown in the Program Output and Execution Time section.
---
## Boundary Check
[insert screenshot of boundary check for SIMD XMM and SIMD YMM]

---
## Overall Results Analysis
[insert comparison of all implementations]
[insert explanation of which is faster, why, and why the speedup may differ from theoretical expectations]

---
## Implementation Discussion
[insert problems encountered and solutions]
[insert unique methodology used and AHA moments]
