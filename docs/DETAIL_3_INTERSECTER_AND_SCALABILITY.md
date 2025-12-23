

## 교차

카메라에서 쏘는 Ray와 교차하는 Object만이 화면에 Rendering 되는 것입니다.  

발사된 Ray에 어떤 구와 교차하는 지 판별해야 합니다.

<details>
  <summary>call stack 및 설명</summary>  
  https://github.com/SeJin0214/software-raytracer/blob/main/core/render.c#L27  
  https://github.com/SeJin0214/software-raytracer/blob/main/core/render.h#L52  
  https://github.com/SeJin0214/software-raytracer/blob/main/core/render.h#L34  
  <br>  
  모든 구 오브젝트를 직선의 벡터 방정식과 구의 방정식을 이용하여 판별합니다.  
  해가 2개라면 교차되는 것이고, 해가 양수여야 앞에 있어야 합니다. 또한 기존의 값보다 작아야 카메라에 제일 가까운 것으로 판별됩니다.  
  https://github.com/SeJin0214/software-raytracer/blob/main/core/sphere.c#L51-L76  

  > 평면, 원기둥, 원뿔 모두 각자의 방정식을 이용해 판별합니다.
  
</details>


## 확장성

오브젝트마다 담을 ArrayList를 만들게 될 경우, 아래의 코드처럼 반복문도 추가로 작성해야 하는 번거로움이 있었습니다.  

```
// 의사 코드
for (int i = 0; i < spheres.size(); ++i)
{
      // is_hit
}

for (int i = 0; i < planes.size(); ++i)
{
      // is_hit
}

...

```
또한 구, 평면, 원기둥, 여기에 원뿔도 추가될 계획이 있었고, 오브젝트마다 이동, 회전, 스케일 연산도 만들어야 하기 때문에 <mark>일반화에 대한 필요성</mark>을 느꼈습니다.  
함수포인터를 활용한 동적 바인딩을 사용할 경우, <mark>인라인을 못해 성능은 조금 느리더라도 유지보수와 확장성이 좋은 구조</mark>가 나올 거라 생각했습니다.  
이에 따라 <mark>OOP의 상속 및 다형성을 흉내내는 구조</mark>를 작성했습니다.  
상속은 메모리가 한 덩어리인 것을 이용하였습니다.  
https://github.com/SeJin0214/software-raytracer/blob/main/core/solid_shape.h#L33-L46
https://github.com/SeJin0214/software-raytracer/blob/main/core/render.h#L38-L49
https://github.com/SeJin0214/software-raytracer/blob/main/core/sphere.h#L20-L24





