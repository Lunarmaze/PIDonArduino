#include <PID_v1.h>

#define PIN_INPUT 0 //입력 신호핀 정의
#define PIN_OUTPUT 3 //출력 신호핀 정의


double Setpoint, Input, Output;

double aggKp=4, aggKi=0.2, aggKd=1; //각각의 비례(Proportional), 적분(Integral),미분(Derivative) 상수 값을 조정하며 PID제어기를 튜닝해야함. << 비교적 aggressive 한 수치

double consKp=1, consKi=0.05, consKd=0.25; //각각의 비례(Proportional), 적분(Integral),미분(Derivative) 상수 값을 조정하며 PID제어기를 튜닝해야함. << 비교적 constrain한 수치

PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT); //PID 라이브러리를 통한 객체 생성, DIRECT: Input 증가시 Output을 감소시킴 / REVERSE: Input 감소시 Output을 증가시킴

void setup()
{
  Serial.begin(9600);
  Setpoint = 100; //목푯값을 100으로 설정
  myPID.SetMode(AUTOMATIC); // SetMode를 AUTO로 설정
  myPID.SetOutputLimits(10, 240); //PID 출력값(Output)의 Min(최솟값)과 Max(최댓값) 설정가능
}

void loop()
{
  Input = map(analogRead(PIN_INPUT),0,1024,0,255); //가변저항으로 Input값을 아날로그 신호로 입력
  myPID.SetTunings(consKp, consKi, consKd); //상수값들을 실시간으로 변동시키고 싶을 때 필요
  myPID.Compute(); //PID 제어기 on
  
  
  Serial.print(Input); // <~~~
  Serial.print(" , ");
  Serial.print(Output);
  Serial.print(" , ");
  Serial.println(Setpoint); // ~~~ 시리얼 플로터 및 시리얼 모니터로 입출력, 목푯값 확인
}
