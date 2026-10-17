# CEPARCO SIMD Programming Project
**Group Members**
- Hernaez, Raeka Estrelle
- Liwanag, Ram Miguel
- Serrano, Paul Rhazzel
- Tiu, Kyle 
---
## Program Output and Execution Time
[insert screenshot of the program output with execution time for all cases]

---
## Comparative Table and Performance Analysis
### Debug Results
Each kernel automatically runs 30 times, and the average execution time is recorded below:
| Vector Size | C (ms) | x84-64 (ms) | SIMD XMM (ms) | SIMD YMM (ms) |
|-------------|--------|-------------|---------------|---------------|
| 2<sup>20</sup> | 2.228727 ms | 0.872700 ms | 0.618217 ms | 0.489837 ms |
| 2^26 | 150.110820 ms | 51.171017 ms | 37.480680 ms | 37.028573 ms |
| 2^28 | 589.386130 ms | 244.100700 ms | 145.379133 ms | 139.506310 ms |

### Release Results
Each kernel automatically runs 30 times, and the average execution time is recorded below:
| Vector Size | C (ms) | x84-64 (ms) | SIMD XMM (ms) | SIMD YMM (ms) |
|-------------|--------|-------------|---------------|---------------|
| 2^20 | 0.610970 ms | 0.788550 ms | 0.496523 ms | 0.493613 ms |
| 2^26 | 34.946617 ms | 42.264160 ms | 37.312290 ms | 36.982870 ms |
| 2^28 | 150.827237 ms | 196.881110 ms | 151.298413 ms | 147.800773 ms |

### Analysis
[insert analysis of performance and speedup (how many times faster, why is it faster, etc.)]

---
## Correctness Check
### C
[insert screenshot of program output with correctness check]
### x86-64
[insert screenshot of program output, including correctness check]
### SIMD XMM register
[insert screenshot of program output, including correctness check]
### SIMD YMM register
[insert screenshot of program output, including correctness check]

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
