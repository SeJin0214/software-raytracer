

## 전역 조명(Global Illumination)

Specular 까지 구현하게 되면, 아래의 사진처럼 하이라이트가 생기게 됩니다.  
<img width="256" height="256" alt="image" src="https://github.com/user-attachments/assets/e1a36cfa-4475-4fc4-9592-fd188c432222" />  
그러나, 이것은 빛만 적용된 것이지  
알고 있던 레이트레이싱이 적용된 사진과는 거리가 멀어 실망하였습니다.  

전역 조명까지 구현해야 알고 있던 레이트레이싱이 나온다는 것을 알게 되었고, 요구사항에 없던 기능을 흉내냈습니다.  

<img width="256" height="256" alt="image" src="https://github.com/user-attachments/assets/c578e579-4d00-456c-af9a-e25645c30207" />



<details>
  <summary>call stack and description</summary>
  https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/render.c#L74-L75
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/render.c#L83
빛의 반사각에 닿는 물체도 하나의 광원이라 생각했습니다.  
표면의 색상을 구할 때, trace_reflection_color 함수도 호출하여 빛의 반사각에 닿는 물체의 빛까지 반영합니다.  
  https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/render.h#L63-L87

  
</details>




## 참고 자료

[한정현 컴퓨터그래픽스 16장](https://www.youtube.com/watch?v=E35m-vRm_KY&list=PLYEC1V9tJOl03WLDoUEKbiYW_Xt4W6LTl&index=17)






