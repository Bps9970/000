//  Пиксельный шейдер Шушкова  { Shader Model 4 Level 9_3 (/4_0_level_9_3) }
//             2:04 02.06.2022

float4 main() : SV_TARGET
{

	// given
	float2x2 fMatrix = { 1.0f, 1.1f,       // row1
								   2.0f, 2.1f };  //  row2
	 float tempo;
	 float R;           // Базовая коррекция
	 const  int W = 1920;
	 const int  H  = 1020;
	 R = sqrt((W / H) * (H / W));
	 const int  iterMax = 100;

	 for  ( int i = 0;  i < iterMax;  i++ )
	 {

		 tempo = fMatrix._m00; 
		 tempo = tempo * i *R;
		 tempo = fMatrix._m11;
		 tempo = tempo * i * R;
		 tempo = fMatrix._11;
		 tempo = tempo * i*R;
		 tempo = fMatrix._22;
		 tempo = tempo * i * R;
	 }

	return float4 ( 1.0f, 1.0f, 1.0f, 1.0f );
}