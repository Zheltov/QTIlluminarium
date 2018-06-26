# QTIlluminarium

Implementation of the algorithm for visualization of 3D scenes by local estimations of the Monte Carlo method 

Реализация двойной локальной оценки метода Монте-Карло для визуализации трехмерных сцен на Qt (C++).

Зависимости:
- boost
- embree

После компиляции копируем Content в место сборки. Запускам "Render" на главной форме. После запуска всех потоков можно остановить визуализацию StopRender и получить финальное изображение.
Проект создан не как конечный продукт, а только тот минимум что был неодходим в рамках работы над диссертацией.

## Примеры визуализаций:
![alt text](images/01_main_window.png)

![][img01]

[img01]: https://github.com/Zheltov/QTIlluminarium/blob/master/Images/01_main_window.png