# QTIlluminarium

Implementation of the algorithm for visualization of 3D scenes by local estimations of the Monte Carlo method 

Реализация двойной локальной оценки метода Монте-Карло для визуализации трехмерных сцен на Qt (C++). Локальные оценки также известны как instant radiosity.

После компиляции копируем Content в место сборки. Запускам "Render" на главной форме. После запуска всех потоков можно остановить визуализацию StopRender и получить финальное изображение.

** Проект создан не как конечный продукт, а только тот минимум, который был неодходим в рамках работы над диссертацией **


## Зависимости:
- boost
- embree


## Подробнее о локальных оценках

- Budak V.P., Zheltov V.S., Lubenchenko A.V., Freidlin K.S., Shagalov O.V. A FAST AND ACCURATE SYNTHETIC ITERATION-BASED ALGORITHM FOR NUMERICAL SIMULATION OF RADIATIVE TRANSFER IN A TURBID MEDIUM // Atmospheric and Oceanic Optics. 2017. Т. 30. № 1. С. 70-78. 
- Budak V., Zheltov V., Notfulin R., Chembaev V. RELATION OF INSTANT RADIOSITY METHOD WITH LOCAL ESTIMATIONS OF MONTE CARLO METHOD // Journal of WSCG. 2016. 
- Zheltov V.S., Budak V.P. LOCAL MONTE CARLO ESTIMATION METHODS IN THE SOLUTION OF GLOBAL ILLUMINATION EQUATION // В сборнике: 22nd International Conference in Central Europe on Computer Graphics, Visualization and Computer Vision, WSCG 2014, Communication Papers Proceedings - in co-operation with EUROGRAPHICS Association 22. 2015. С. 25-30. 
- Чембаев В.Д., Будак В.П., Желтов В.С., Нотфулин Р.С., Селиванов В.А. USAGE OF LOCAL ESTIMATIONS AT THE SOLUTION OF GLOBAL ILLUMINATION EQUATION // В сборнике: ГРАФИКОН'2015 Труды Юбилейной 25-й Международной научной конференции. 2015. С. 7-11. 
- Budak V.P., Zheltov V.S., Lubenchenko A.V., Shagalov O.V. ON THE EFFICIENCY OF ALGORITHMS OF MONTE CARLO METHODS // В сборнике: Proceedings of SPIE - The International Society for Optical Engineering 21, Atmospheric Physics. Сер. "21st International Symposium on Atmospheric and Ocean Optics: Atmospheric Physics" 2015. С. 96801P. 

## Примеры визуализаций:
![][img01 | width=600]
![][img02]
![][img03]

[img01]: https://github.com/Zheltov/QTIlluminarium/blob/master/Images/01_main_window.png
[img02]: https://github.com/Zheltov/QTIlluminarium/blob/master/Images/02_cornel_box.png
[img03]: https://github.com/Zheltov/QTIlluminarium/blob/master/Images/03_sponza.png