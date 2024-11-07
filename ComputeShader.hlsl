/*
* 
 * Вычислительный шейдер Шушкова
 * Программист - Помазков М.В.
 * Email - bps9970@gmail.com
 * Моб. телефон - 8(914) 234 - 02 - 11
 * Peпозиторий GitHib  https://githib/Bps9970/000 (публичный репозитрий)
 * 
 */

float4x4 World;
float4x4 View;
float4x4 Projection;

float Shader()
{
	// = = = = = = = = = = = = = = = = = = =
	float pi = 3.14;
	float e = 2.71828;
	float de = 0;
	float x = 0;
	float om = 0;
	float  mi = 0;
	float al = 0;
	// = = = = = = = = = = = = = = = = =
	
	// [1] Вычисляем основание для е
	de = pow(( x - mi), 2) / (pow( al * om, 2));
	// [2] Вычисляем e(dx)
	de = (pow( e, de));
	// [3] Вычисляем 1/(...)
	x = 1/(sqrt( 2* pi *(pow( om, 2))));
	// [4] Вычисляем окончательного результата
	x = x * de;
	printf("X = ", x);
	//World = x;
}

void main( uint3 DTid : SV_DispatchThreadID )
{
	
	[numthreads(4, 4, 1)];   // Ошибка	X3084	'numthreads(X,Y,Z)'
	/*VertexShaderInput pos;
	VertexShaderFunction(pos);
	VertexShaderOutput VS;
	*/
	
	Shader();
	
}
