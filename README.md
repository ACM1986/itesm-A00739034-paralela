# Proyecto OpenMP - Suma Paralela de Arreglos

## ¿Qué hace este proyecto?

✅ Suma dos arreglos en paralelo (porque esperar es aburrido)  
✅ Puedes elegir valores random o poner los tuyos propios  
✅ Mide qué tan rápido va (spoiler: ¡muy rápido!)  
✅ Te muestra que todo salió bien  
✅ Imprime los resultados para que veas la magia  

## Lo que necesitas tener instalado

- Visual Studio 2019 o más reciente (con las herramientas de C++)
- El compilador MSVC (ya viene con Visual Studio)
- Windows 10 o superior (aunque si tienes Windows 11, también jala)

## Cómo configurar el proyecto en Visual Studio

### La forma fácil (ya está todo listo):

1. Abre Visual Studio
2. Dale a **File > Open > Project/Solution**
3. Busca la carpeta del proyecto y abre `OpenMP_ArraySum.sln`
4. ¡Y ya! El proyecto ya tiene OpenMP configurado, así que solo corre y corre

### Por si acaso (verificar OpenMP manualmente):

Oye, si por alguna razón quieres asegurarte de que OpenMP esté activado o necesitas hacerlo manual:

1. Click derecho en el proyecto (está en el **Solution Explorer**)
2. Entra a **Properties** (Propiedades)
3. Navega a **Configuration Properties > C/C++ > Language**
4. Busca **Open MP Support** y ponlo en **Yes (/openmp)**
5. Dale OK y listo

**Pro tip:** Asegúrate de que esto esté activado tanto en Debug como en Release, y en todas las plataformas (x86/x64). No querrás sorpresas después.

## Cómo Compilar y Ejecutar
¿Cómo lo corro?

### Opción A: Desde Visual Studio (la más cómoda):

1. Abre `OpenMP_ArraySum.sln`
2. Elige si quieres Debug o Release (te recomiendo x64)
3. Dale **F5** si quieres debuguear
4. O mejor aún, **Ctrl+F5** para correrlo directo sin debug (va más rápido)

### Opción B: Modo hardcore (línea de comandos):

Si eres de los que les gusta la terminal:

```bash
# Ve a la carpeta del proyecto
cd "OpenMP_ArraySum"

# Compila
cl /EHsc /openmp main.cpp

# ¡A correr!
```¿Cómo usar el programa?

Cuando lo ejecutes, te va a salir un menú así:

```
=== SUMA PARALELA DE ARREGLOS CON OpenMP ===
Cantidad de elementos: 1000

Seleccione una opcion:
1. Generar valores aleatorios
2. Ingresar valores manualmente (solo primeros 10)
Opcion:
```

### Opción 1: Modo aleatorio (mi favorita)
Dale 1 y el programa generará automáticamente 1000 números random entre 0 y 99. Es perfecto cuando solo quieres ver cómo funciona sin complicarte la vida.

### Opción 2: Modo manual (para los perfeccionistas)
Aquí tú pones los primeros 10 números de cada arreglo. Los otros 990 se llenan solos con valores random. Es útil cuando quieres probar casos específicos o simplemente quieres tener control.eros 10 valores de cada arreglo
- Los elementos restantes (10-999) se llenan aleatoriamente
- Útil para verificar casos específicos

## Salida del Programa

El programa muestra:
¿Qué voy a ver en la pantalla?

El programa te va a mostrar un montón de info interesante:

1. **Los arreglos originales**: Te muestra los primeros 20 números de cada uno
2. **Cuántos hilos se están usando**: Para que veas el poder de tu CPU
3. **Qué tan rápido fue**: El tiempo exacto que tardó (prepárate para sorprenderte)
4. **El resultado**: Los primeros 20 números de la suma
5. **Una tabla de verificación**: Para que compruebes que todo está bien

Por ejemplo, verías algo asíINALES ===
Arreglo A (primeros 20 elementos): 45 12 89 34 67 ...
Arreglo B (primeros 20 elementos): 23 56 78 90 12 ...

=== PROCESAMIENTO PARALELO ===
Numero de hilos disponibles: 8
Suma completada en 0.000234 segundos

=== RESULTADO ===
Arreglo Resultado (A+B) (primeros 20 elementos): 68 68 167 124 79 ...

=== VERIFICACION (primeros 10 elementos) ===
Indice  A[i]      B[i]      Resultado[i]   A[i]+B[i]      Correcto?
----------------------------------------------------------------------
0       45        23        68             68             SI
1       12        56        68             68             SI
...
```

## Estructura del Código

### Funciones Principales:
¿Cómo está hecho el código?

### Las funciones importantes:

- `imprimirArreglo()`: Hace lo que su nombre dice, imprime los primeros N elementos
- `main()`: El cerebro de la operación, donde pasa toda la magia

### Las directivas de OpenMP que usamo
```
Esta directiva distribuye las iteraciones del bucle entre múltiples hilos.

```cpp
#pragma omp parallel
{
    #pragma omp single
    // código...
}
```
Obtiene información sobre los hilos en ejecución.

## La magia del código paralelo explicada

Mira esta parte del código:

```cpp
// SUMA PARALELA usando OpenMP
#pragma omp parallel for
for (int i = 0; i < N; i++) {
    arregloResultado[i] = arregloA[i] + arregloB[i];
}
```

¿Qué está pasando aquí? Bueno, es súper interesante:
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

---
**Fecha:** Febrero 2026
