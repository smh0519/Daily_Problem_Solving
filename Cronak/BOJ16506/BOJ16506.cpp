#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <array>
#include <queue>
#include <map>
using namespace std;

int main() {
    // ============================================
    // 1단계: opcode를 4비트 이진수로 변환하는 매핑 테이블 생성
    // ============================================
    // 문제에서 주어진 14개의 명령어를 각각 4비트 이진수로 매핑
    // 예: ADD는 0번 -> 0000(2진수)
    map<string, string> opcodeMap;
    opcodeMap["ADD"] = "0000";   // 0번 명령어
    opcodeMap["SUB"] = "0001";   // 1번 명령어
    opcodeMap["MOV"] = "0010";   // 2번 명령어
    opcodeMap["AND"] = "0011";   // 3번 명령어
    opcodeMap["OR"] = "0100";    // 4번 명령어
    opcodeMap["NOT"] = "0101";   // 5번 명령어
    opcodeMap["MULT"] = "0110";  // 6번 명령어
    opcodeMap["LSFTL"] = "0111"; // 7번 명령어 (Left Shift)
    opcodeMap["LSFTR"] = "1000"; // 8번 명령어 (Logical Right Shift)
    opcodeMap["ASFTR"] = "1001"; // 9번 명령어 (Arithmetic Right Shift)
    opcodeMap["RL"] = "1010";    // 10번 명령어 (Rotate Left)
    opcodeMap["RR"] = "1011";    // 11번 명령어 (Rotate Right)

    // ============================================
    // 2단계: 입력 받기 (명령어 개수와 각 명령어)
    // ============================================
    int CommandNumbers; // 명령어 개수
    cin >> CommandNumbers;

    // ============================================
    // 3단계: CommandNumbers개의 명령어를 하나씩 처리
    // ============================================
    for (int i = 0; i < CommandNumbers; i++) {
        string opcode;  // 명령어 이름 (예: "ADD", "ADDC", "MULT" 등)
        int rD, rA, rB; // 레지스터 번호 (0~7)
        int C;          // 상수 값 (0~15, 4비트로 표현 가능)

        // 입력: opcode rD rA rB/C
        cin >> opcode >> rD >> rA >> rB;
        C = rB; // rB와 C는 같은 위치에 입력되므로 동일하게 취급

        // ============================================
        // 4단계: 결과를 저장할 이진수 문자열 생성
        // ============================================
        string result = ""; // 최종 16비트 이진수 결과

        // ============================================
        // 4-1단계: opcode 처리 (5비트)
        // ============================================
        // 명령어 끝에 'C'가 붙어있는지 확인
        // 'C'가 있으면 -> 마지막 비트가 1 (상수 사용)
        // 'C'가 없으면 -> 마지막 비트가 0 (레지스터 사용)
        if (opcode.back() == 'C') {
            // 예: "ADDC"인 경우
            opcode.pop_back(); // 'C' 제거 -> "ADD"로 변환
            result += opcodeMap[opcode]; // "0000" 추가
            result += "1"; // 5번째 비트를 1로 설정 (상수 사용)
        }
        else {
            // 예: "ADD"인 경우
            result += opcodeMap[opcode]; // "0000" 추가
            result += "0"; // 5번째 비트를 0으로 설정 (레지스터 사용)
        }

        // ============================================
        // 4-2단계: 미사용 비트 처리 (1비트)
        // ============================================
        // 6번째 비트는 항상 0
        result += "0";

        // ============================================
        // 4-3단계: rD(목적지 레지스터) 처리 (3비트)
        // ============================================
        // rD는 0~7 사이의 숫자 -> 3비트 이진수로 변환
        // 예: rD=5 -> 101
        // 비효율적 방법: 4부터 하나씩 빼가면서 이진수 만들기
        int temp = rD;
        string rD_binary = "";
        
        // 4로 나눈 몫이 1이면 첫 번째 비트 1, 아니면 0
        if (temp >= 4) {
            rD_binary += "1";
            temp -= 4;
        } else {
            rD_binary += "0";
        }
        
        // 2로 나눈 몫이 1이면 두 번째 비트 1, 아니면 0
        if (temp >= 2) {
            rD_binary += "1";
            temp -= 2;
        } else {
            rD_binary += "0";
        }
        
        // 나머지가 1이면 세 번째 비트 1, 아니면 0
        if (temp >= 1) {
            rD_binary += "1";
        } else {
            rD_binary += "0";
        }
        
        result += rD_binary;

        // ============================================
        // 4-4단계: rA(첫 번째 피연산자 레지스터) 처리 (3비트)
        // ============================================
        // rA도 동일한 방법으로 3비트 이진수 변환
        temp = rA;
        string rA_binary = "";
        
        if (temp >= 4) {
            rA_binary += "1";
            temp -= 4;
        } else {
            rA_binary += "0";
        }
        
        if (temp >= 2) {
            rA_binary += "1";
            temp -= 2;
        } else {
            rA_binary += "0";
        }
        
        if (temp >= 1) {
            rA_binary += "1";
        } else {
            rA_binary += "0";
        }
        
        result += rA_binary;

        // ============================================
        // 4-5단계: rB 또는 C 처리 (4비트)
        // ============================================
        // opcode 끝에 'C'가 있었는지에 따라 달라짐
        // - 'C'가 있었으면: C(상수)를 4비트로 변환 (0~15)
        // - 'C'가 없었으면: rB(레지스터 번호)를 3비트로 변환 + 맨 뒤에 0 추가 (0~7)
        
        temp = rB; // 또는 C (둘 다 같은 값)
        string rB_binary = "";
        
        // 'C'가 있는 경우: 4비트 변환 (8, 4, 2, 1)
        if (opcode.back() == 'C' || result[4] == '1') {
            // 8로 나눈 몫이 1이면 첫 번째 비트 1, 아니면 0
            if (temp >= 8) {
                rB_binary += "1";
                temp -= 8;
            } else {
                rB_binary += "0";
            }
            
            // 4로 나눈 몫이 1이면 두 번째 비트 1, 아니면 0
            if (temp >= 4) {
                rB_binary += "1";
                temp -= 4;
            } else {
                rB_binary += "0";
            }
            
            // 2로 나눈 몫이 1이면 세 번째 비트 1, 아니면 0
            if (temp >= 2) {
                rB_binary += "1";
                temp -= 2;
            } else {
                rB_binary += "0";
            }
            
            // 나머지가 1이면 네 번째 비트 1, 아니면 0
            if (temp >= 1) {
                rB_binary += "1";
            } else {
                rB_binary += "0";
            }
        }
        // 'C'가 없는 경우: 3비트 변환 (4, 2, 1) + 마지막에 0 추가
        else {
            // 4로 나눈 몫이 1이면 첫 번째 비트 1, 아니면 0
            if (temp >= 4) {
                rB_binary += "1";
                temp -= 4;
            } else {
                rB_binary += "0";
            }
            
            // 2로 나눈 몫이 1이면 두 번째 비트 1, 아니면 0
            if (temp >= 2) {
                rB_binary += "1";
                temp -= 2;
            } else {
                rB_binary += "0";
            }
            
            // 나머지가 1이면 세 번째 비트 1, 아니면 0
            if (temp >= 1) {
                rB_binary += "1";
            } else {
                rB_binary += "0";
            }
            
            // 'C'가 없을 때는 마지막 비트 항상 0
            rB_binary += "0";
        }
        
        result += rB_binary;

        // ============================================
        // 5단계: 결과 출력
        // ============================================
        // 총 16비트 이진수 출력
        // 형식: opcode(5) + 0(1) + rD(3) + rA(3) + rB/C(4)
        cout << result << endl;
    }

    return 0;
}