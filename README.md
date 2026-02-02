# Suma Paralela de Arreglos con OpenMP

Este es un proyecto que demuestra cómo usar OpenMP para sumar dos arreglos de 1000 elementos de forma paralela. La idea es ver cómo el procesamiento en paralelo hace las cosas mucho más rápidas.

## ¿Qué hace?

Suma dos arreglos elemento por elemento usando múltiples hilos de tu CPU. Puedes elegir si quieres números aleatorios o poner los tuyos propios. Al final te muestra cuánto tiempo tardó y verifica que todo esté bien.

## Requisitos

- Visual Studio 2019 o superior
- Windows 10+

## Cómo usarlo

1. Abre `OpenMP_ArraySum.sln` en Visual Studio
2. Presiona **F5** o **Ctrl+F5** para ejecutar
3. Elige si quieres valores aleatorios o manuales
4. ¡Listo! Ve los resultados en pantalla

## ¿Qué voy a ver?

El programa te muestra:
- Los primeros 20 elementos de cada arreglo
- Cuántos hilos está usando tu CPU
- El tiempo que tardó (milisegundos)
- Los resultados de la suma
- Una tabla de verificación para confirmar que todo está bien

## La magia del código paralelo explicada

Mira esta parte del código:

```cpp
// SUMA PARALELA usando OpenMP
#pragma omp parallel for
for (int i = 0; i < N; i++) {
    arregloResultado[i] = arregloA[i] + arregloB[i];
}
```

¿Qué está pasando aquí? 
1. Ese `#pragma` le dice al programa "oye, usa todos los hilos que puedas"
2. Automáticamente divide las 1000 sumas entre todos tus núcleos de CPU
3. Cada hilo agarra su pedacito y trabaja independiente
4. ¿Quieres experimentar?

Aquí te dejo algunas ideas para que juegues con el código:

### Hazlo más grande (o más pequeño):
```cpp
const int N = 1000; // Ponle 10000, 100000... ¡o lo que quieras!
```

### Cambia el rango de números random:
```cpp
arregloA[i] = rand() % 100; // En vez de 100, pon 1000 para números más grandes
```

### Fuerza el número de hilos:
Agrega esto antes del código paralelo:
```cpp
omp_set_num_threads(4); // Oblígalo a usar solo 4 hilos (útil para experimentos)
###Si algo no jala...

### Error: "omp.h: No such file or directory"
Tranquilo, esto pasa cuando:
- OpenMP no está activado en las propiedades del proyecto (revisa arriba cómo hacerlo)
- Estás usando un compilador viejo que no soporta OpenMP

### "¿Por qué solo usa 1 hilo?"
Varias razones posibles:
- No compilaste con OpenMP activado (revisa las propiedades del proyecto)
- Tu CPU es de un solo núcleo (poco probable en 2026, pero hey...)
- Agrega un `printf` con `omp_get_num_threads()` para ver qué está pasando

### Errores raros al compilar
- Asegúrate de que el proyecto esté como "Console Application"
- CSi quieres aprender más

- [Documentación oficial de OpenMP](https://www.openmp.org/) - Para cuando quieras ir más profundo
- [OpenMP en Visual C++ (Microsoft)](https://docs.microsoft.com/en-us/cpp/parallel/openmp/openmp-in-visual-cpp) - La guía de Microsoft

## Sobre este proyecto

Lo hice para la materia de Cómputo en la Nube en la Maestría de IA. Es un proyecto educativo para entender cómo funciona la programación paralela. Si tienes dudas o sugerencias, ¡no dudes en preguntar!

---
**Fecha:** Febrero 2026  
**Nota:** Este README fue escrito pensando en que lo leas como si te estuviera explicando un amigo, no un manual técnico aburrido 😊mentation](https://www.openmp.org/)
- [Microsoft OpenMP in Visual C++](https://docs.microsoft.com/en-us/cpp/parallel/openmp/openmp-in-visual-cpp)

## Autor

Proyecto creado para la materia de Cómputo en la Nube - Maestría en IA
Alberto Cortes Murillo
