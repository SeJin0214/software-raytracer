
## 최적화

specular와 GI도 구현하기 전, 1회 렌더링 성능입니다.    

<img width="512" height="128" alt="diffuse" src="https://github.com/user-attachments/assets/ca96f31e-3c57-47e9-b389-06b19c72eaf4" />

렌더링 시간에 0.7초씩이나 소모되어 키 입력마다 뚝뚝 끊겨서 움직였습니다.  
최적화 할 수 있는 방법이 무엇이 있을까 고민하다가, 최적화 플래그 라는 것이 있다는 게 생각났습니다.  

<details>
  <summary>
    최적화 플래그 적용 전, 후
  </summary>
  -O3와 -march=native flag를 넣어주었습니다.
<img width="512" height="128" alt="image (1)" src="https://github.com/user-attachments/assets/2fabfaac-58e6-4170-8fd2-41ef65035355" />

  아쉬운 점 : disassembly를 보았을 때, 컴파일러 최적화 플래그로 SIMD 연산을 유도해봤으나 그러지 못한 연산들이 있었습니다.  
</details>

<details>
  <summary>
    상위 호출 연산 inline으로 변경
  </summary>
  렌더링마다 vector 연산이 많이 호출되고 있지 않을까? 라는 생각을 했습니다.  
  GNU Profiler인 gprof를 이용하여 vector 연산이 몇 천만 번 호출되는 것을 확인했습니다.  
  함수 오버헤드를 줄일 경우, 성능이 매우 빨리질 거라 생각했습니다.  
  vector 연산을 모두 inline 하였고, 아래와 같은 속도가 나오게 되었습니다.  
  <br>
  <img width="256" height="512" alt="image (2)" src="https://github.com/user-attachments/assets/1c970447-4f11-4d3d-a919-fd37dfe48942" />  
  <br>
  <br>
  이후 호출량이 많았던 함수도 모두 inline 하였습니다.  
  <br>
  <img width="256" height="512" alt="image (3)" src="https://github.com/user-attachments/assets/1d68f6af-2a63-4a05-ad6c-ce0716383324" />  

</details>


<details>
  <summary>
    멀티쓰레드 16등분 렌더링
  </summary>

  멀티 쓰레드를 사용하게 될 경우, 더 많은 코어를 이용하기 때문에 더 빠를 것이라 생각했습니다.  
  요즘 나오는 컴퓨터가 8개의 코어를 갖고 있다 들어, 코어 하나당 2개의 쓰레드를 할당했습니다.  
  canvas size에 맞게 가로, 세로 4등분 하여 16개의 쓰레드를 만들어 각 타일의 색을 넣게 했습니다.
  https://github.com/SeJin0214/software_raytracing/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/main.c#L72-L96
  <br>
  <img width="175" height="496" alt="image" src="https://github.com/user-attachments/assets/9526297e-20eb-4e2b-886e-79f5e70d5fec" />
  <br>
  <br>
  이후 다중 조명, GI 등을 구현하게 되었고 0.02초 정도의 렌더링 시간을 확보했습니다.  
  <br>
  <br>
  아쉬운 점 : 컴퓨터 정보에서 CPU 코어 개수를 파악하는 것이 아닌, 어림짐작으로 파악했습니다. 다음엔 명령어 또는 설정에서 확인하려 합니다.  

</details>







