# CEPARCO SIMD Programming Project
**Group Members**
- Hernaez, Raeka Estrelle
- Liwanag, Ram Miguel
- Serrano, Paul Rhazzel
- Tiu, Kyle 
---
## Program Output and Execution Time
[insert screenshot of the program output with execution time for all cases]
### Debug Program Output
### 2<sup>20</sup>
<img width="500" height="350" alt="image" src="https://github.com/user-attachments/assets/e4824f90-ed5f-4629-a438-3c6f5dd30d8b" />
### 2<sup>26</sup>
<img width="1294" height="1160" alt="image" src="https://github.com/user-attachments/assets/333239c2-6d5c-4dd6-a2c9-a0bbe1c71b00" />
### 2<sup>28</sup> (as alternative for 2<sup>30</sup>)
<img width="1304" height="1158" alt="image" src="https://github.com/user-attachments/assets/9c1ffa74-a40a-4a51-a66d-34ff40b6cce3" />

### Release Program Output
### 2<sup>20</sup>
<img width="1300" height="1168" alt="image" src="https://github.com/user-attachments/assets/e80e6e0c-9feb-4490-948b-bd2318f8c5bd" />
### 2<sup>26</sup>
<img width="1294" height="1160" alt="image" src="https://github.com/user-attachments/assets/61b74911-8cd4-43da-94dc-90f81d3b2e13" />
### 2<sup>28</sup> (as alternative for 2<sup>30</sup>)
<img width="1290" height="1154" alt="image" src="https://github.com/user-attachments/assets/837951a8-565d-48ce-8d9a-9afe38821a81" />

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
