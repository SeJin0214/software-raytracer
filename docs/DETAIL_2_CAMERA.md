
## 좌표계
DirectX로 학습 전이를 위해 왼손 좌표계를 사용했습니다.  
<img width="245" height="290" alt="image" src="https://github.com/user-attachments/assets/c904ef1b-84b3-41df-9294-750fd2f5ccf1" />



## Render  
카메라로 렌더링 하기 위해 그림과 같이 픽셀에 Ray를 매핑하여 발사했습니다.  
<img width="381" height="202" alt="image" src="https://github.com/user-attachments/assets/e5a52c8a-926e-4429-b14c-29c4bc9adb0b" />

발사된 Ray로 해당 Pixel의 Color 값을 가져오고, Image buffer에 값을 넣습니다.  
https://github.com/SeJin0214/software-raytracer/blob/8ebf8f50f5dd47df6ce41f5744cbc4353ea483fd/core/render.c#L47-L50

Pixel마다 Ray를 어떻게 발사해야 할 지 고민하다가 다음과 같은 코드를 작성하게 되었습니다.  
<details><summary>mappied_ray</summary>
  선형 보간 공식에 t = field of view / Pixel length를 넣어, Pixel마다 카메라 각도를 구했습니다.
https://github.com/SeJin0214/software-raytracer/blob/8ebf8f50f5dd47df6ce41f5744cbc4353ea483fd/core/render.c#L36-L46
  이후 tan를 이용하여 카메라 각도에 해당하는 x와 y를 구하여 Ray의 방향을 지정해주었습니다.
https://github.com/SeJin0214/software-raytracer/blob/8ebf8f50f5dd47df6ce41f5744cbc4353ea483fd/core/render.c#L56-L71
</details>













