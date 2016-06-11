#version 120

uniform sampler2D diffuse;
//uniform sampler2D pot;

varying vec2 texCoord0;
varying vec3 normal0;

void main()
{
	float lighting = dot(-vec3(0,0,2), normal0);
	gl_FragColor = texture2D(diffuse, texCoord0) * lighting; //Применяем освещение - умножаем цвет текстуры на некоторое число, в данном случае - на косинус угла между нормалью и светом
}