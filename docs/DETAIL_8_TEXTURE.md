
## 텍스처

텍스처를 입히고 bump map을 입혀야 합니다.  

<details>
  <summary>
    bump, texturing call stack and description
  </summary>

매핑된 키에 따라 texture 타입을 변경합니다.  
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/solid_shape.c#L75-L86

https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/render.c#L23
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/header/render.h#L45
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/header/render.h#L32
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/header/render.h#L39

  <br>
sphere의 경우  
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/sphere.c#L48
여기서 bump map을 위한 normal을 바꿔줍니다.  
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/header/sphere.h#L31-L41

  <br>
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/header/solid_shape_getter.h#L59-L60
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/header/solid_shape_getter.h#L48-L49
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/header/solid_shape_getter.h#L52

uv 좌표를 구하는 공식은 가져다 사용했습니다.  
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/core/sphere.c#L48-L62
이후 uv좌표에 맞게 texel color를 지정했습니다.  
https://github.com/SeJin0214/software-raytracer/blob/c26ea3edfce9724883d59552b356a3dc46e9580e/header/solid_shape_getter.h#L32-L46

</details>











