
## 텍스처

텍스처를 입히고 bump map을 입혀야 합니다.  

<details>
  <summary>
    bump, texturing call stack and description
  </summary>

매핑된 키에 따라 texture 타입을 변경합니다.  
https://github.com/SeJin0214/software-raytracer/blob/d241ea963ac7fb185d98b1f6f365e270ceed0816/bonus/solid_shape.c#L75-L85

https://github.com/SeJin0214/software-raytracer/blob/7438b74905f9bfbb46bd6ae0f7109aed1b41ab39/bonus/render.c#L27
https://github.com/SeJin0214/software-raytracer/blob/7438b74905f9bfbb46bd6ae0f7109aed1b41ab39/bonus/render.h#L52
https://github.com/SeJin0214/software-raytracer/blob/7438b74905f9bfbb46bd6ae0f7109aed1b41ab39/bonus/render.h#L34
https://github.com/SeJin0214/software-raytracer/blob/7438b74905f9bfbb46bd6ae0f7109aed1b41ab39/bonus/render.h#L46

  <br>
sphere의 경우  
https://github.com/SeJin0214/software-raytracer/blob/a8509ea4d3c6e71d1d3177496a27a5171c9cdc29/bonus/sphere.c#L51
여기서 bump map을 위한 normal을 바꿔줍니다.  
https://github.com/SeJin0214/software-raytracer/blob/a8509ea4d3c6e71d1d3177496a27a5171c9cdc29/bonus/sphere.h#L50-L59

  <br>
https://github.com/SeJin0214/software-raytracer/blob/a8509ea4d3c6e71d1d3177496a27a5171c9cdc29/bonus/solid_shape_getter.h#L59-L60
https://github.com/SeJin0214/software-raytracer/blob/a8509ea4d3c6e71d1d3177496a27a5171c9cdc29/bonus/solid_shape_getter.h#L48-L49
https://github.com/SeJin0214/software-raytracer/blob/a8509ea4d3c6e71d1d3177496a27a5171c9cdc29/bonus/solid_shape_getter.h#L52

uv 좌표를 구하는 공식은 가져다 사용했습니다.  
https://github.com/SeJin0214/software-raytracer/blob/7438b74905f9bfbb46bd6ae0f7109aed1b41ab39/bonus/sphere.h#L33-L47
이후 uv좌표에 맞게 texel color를 지정했습니다.  
https://github.com/SeJin0214/software-raytracer/blob/a8509ea4d3c6e71d1d3177496a27a5171c9cdc29/bonus/solid_shape_getter.h#L32-L46

</details>










