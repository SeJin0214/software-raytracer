

## 환경  
1. 운영체제       : Ubuntu 22.04.3 LTS  
2. 언어 : C  
3. 빌드    : makefile
4. 라이브러리 : MiniLibX
6. 코딩 표준 : 42 norminette    
             함수 25줄 이하  
             한 라인 길이 80이하  

## 요구사항  
1. 허용 함수 및 라이브러리 목록  
  open, close, read, write, printf, malloc, free, perror, exit, math.h  
  
2. .rt 파일 형식에 맞춰서 파싱할 것(요소가 올바르지 않거나 .rt가 파일이 아니면 유효하지 않음)  
<img width="512" height="128" alt="image" src="https://github.com/user-attachments/assets/5385cea1-e4b8-41c1-8565-f8588d2f8ab3" />

3. 구, 평면, 원기둥, 원뿔 등의 오브젝트 구현 할 것  
4. 키 매핑에 따라 이동, 스케일, 회전 구현 할 것  
5. diffuse, ambient, specular, Multi right, shadow, texture, checkboard를 구현할 것  



## Parser
.rt 파일 형식에 맞춰 Object 초기화를 위해 parser를 만들었습니다.  
올바른 오브젝트는 직접 만든 ArrayList에 넣어 world 내에서 관리했습니다.  

https://github.com/SeJin0214/software-raytracer/blob/2feac11d4a3300c29a66d0eebb436d770b450469/bonus/parse_solid_shape.c#L110-L111

<details><summary>Parsing call stack 및 설명</summary>
https://github.com/SeJin0214/software-raytracer/blob/e3334c43b6227cf48d3079cd3b6f320f2e70e4b9/bonus/main.c#L32  
https://github.com/SeJin0214/software-raytracer/blob/5ce16e5bdffa75c7007f522564e2123fa6595858/bonus/parse.c#L53  
https://github.com/SeJin0214/software-raytracer/blob/5ce16e5bdffa75c7007f522564e2123fa6595858/bonus/parse.c#L82  
<br>
유지보수와 가독성을 위해 Enum으로 attribute를 명시해주었습니다.  
<mark>attribute의 포맷(x,y,z의 요소의 개수 등)이 올바르지 않거나, value 값이 올바르지 않으면</mark> 실패하도록 하였습니다.   
<br>
<br>

> 카메라, 라이트, 구, 평면, 원뿔 모두 비슷한 코드로 동작합니다.
https://github.com/SeJin0214/software-raytracer/blob/0737dd26129d40eaf5ab1bea73a2a7b2ff1e713d/bonus/parse.h#L63-L71  
https://github.com/SeJin0214/software-raytracer/blob/2feac11d4a3300c29a66d0eebb436d770b450469/bonus/parse_solid_shape.c#L87-L95  
https://github.com/SeJin0214/software-raytracer/blob/2feac11d4a3300c29a66d0eebb436d770b450469/bonus/parse_solid_shape.c#L115-L125
</details>






















