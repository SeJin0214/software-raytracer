

## 조명

Phong light model의 4개의 조명 3개의 조명을 구현해야 합니다.  
1. diffuse : 난반사라 하며, 여러 방향으로 균일하게 흩어져 어느 방향으로 봐도 동일하게 보인다.  
2. ambient : 주변광이라 하며, 공간 전체에 은은하게 퍼져있는 빛     
3. specular : 정반사라 하며, 카메라 각도에 따라 하이라이트가 보인다.  
  
color를 0 ~ 1이 아닌 0 ~ 255의 범위로 잡았습니다.  

카메라로 쏜 Ray가 교차되는 Object가 있다면, Object의 색상을 구했을 것입니다.  
색상을 이용해 아래의 코드처럼 각 조명을 계산하고 더해야 합니다.

diffuse + ambient + specular = pixel color
https://github.com/SeJin0214/software-raytracer/blob/aab4f628e9528c4f39fa238485b7db2cc978e1d4/bonus/render.c#L84-L100

<details><summary>implement diffuse and ambient</summary>
<img width="745" height="868" alt="image" src="https://github.com/user-attachments/assets/2bf81828-5148-4166-8dae-05fd2500b5bd" />
</details>  


<details><summary>diffuse and ambient description</summary>
https://github.com/SeJin0214/software-raytracer/blob/d544078fce1685fb2c4598b6e944ffeddbe124da/bonus/light.h#L19-L31  
  표면의 노멀 벡터와 중심에서 빛으로 가는 벡터의 내적을 구하여 빛의 세기를 구하였습니다.  
https://github.com/SeJin0214/software-raytracer/blob/d544078fce1685fb2c4598b6e944ffeddbe124da/bonus/light.h#L33-L49

  albedo는 물체가 빛을 반사하는 정도를 나타내는 척도이며, 두 조명 모두 albedo 연산을 추가로 해줬습니다.  
  https://github.com/SeJin0214/software-raytracer/blob/aab4f628e9528c4f39fa238485b7db2cc978e1d4/mandatory/shadow.h#L47-L58  
  
</details>
<details><summary>specular description</summary>
  표면의 빛 반사각과 표면에서 카메라로 향하는 벡터가 15도 이내 정도로 닮을 때만 하이라이트가 보이게 해주었습니다.
https://github.com/SeJin0214/software-raytracer/blob/d544078fce1685fb2c4598b6e944ffeddbe124da/bonus/light.h#L69-L82
</details>  
  
  
## 그림자
해당 표면이 그림자 져야 하는지 판단하는 코드입니다.  
1. 빛에서 표면까지 Ray를 쏩니다.  
2. 부딪히는 Object가 있다면, 그 Object에서 빛까지의 거리와 표면에서 빛까지 거리를 비교합니다.  
3. 표면에서 빛까지의 거리가 더 크다면 Object에 가려져 있는 것이므로 그림자가 지는 것으로 판단합니다.  
https://github.com/SeJin0214/software-raytracer/blob/aab4f628e9528c4f39fa238485b7db2cc978e1d4/mandatory/shadow.h#L17-L45



### 참고 자료

[한정현 컴퓨터그래픽스 9장 라이팅](https://www.youtube.com/watch?v=_uIjVpAM9l8&list=PLYEC1V9tJOl03WLDoUEKbiYW_Xt4W6LTl&index=10)





















