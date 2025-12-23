
## Action

아래의 표와 같은 Action을 할 수 있어야 합니다.  
|  | 오브젝트 | 카메라 | 조명 |  
|------|------|------|------|
| 이동   |    O   |    O   |   O  |  
| 회전   | O | O | X |  
| 스케일 | O | X | X |  
  

<details>
  <summary>
    key mapping
  </summary>
  이미지와 같이 키보드를 매핑했습니다.
  <img width="840" height="528" alt="image" src="https://github.com/user-attachments/assets/8f56c910-2c95-4094-b40a-b295ba1074aa" />  
  mlx 라이브러리에 key 입력 시 실행할 이벤트를 등록해둡니다.  
  https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/main.c#L44
  <br>
  <br>
  단순하게 조건문으로 key input을 체크했습니다.  
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/c26ea3edfce9724883d59552b356a3dc46e9580e.c#L51-L70
  <br>
  <br>
  다른 Action이나 오브젝트도 동일하게 해주었습니다.   
  
  https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/input_camera.c#L16-L36
  <br>
  Enum과 define은 input.h 파일에서 볼 수 있습니다.  
  <br>
  https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/header/input.h#L55
  
</details>

<details>
  <summary>
    Local Basis
  </summary>
  
  이전에 봤던 추상화 시킨 부모 구조체입니다.  
  local_basis 덕분에 object는 동일한 코드로 작동합니다.  
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/header/solid_shape.h#L33-L37

  local_basis를 기준으로 x, y, z를 움직입니다.  
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/solid_shape.c#L24-L45

  local_basis를 기준으로 회전합니다.  
  회전은 쿼터니언 공식을 가져다 사용했습니다.  
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/solid_shape.c#L47-L70

  다른 이동 및 회전 연산도 동일한 로직으로 작동합니다.

</details>
  



  

