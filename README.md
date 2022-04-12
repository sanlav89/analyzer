# Анализатор гамма-спектров с алгоритмом идентификации радионуклидов, основанном на сверточных нейронных сетях  
Программа с простым GUI для демонстрации возможности применения сверточных нейронных сетей (convolution neural network, CNN) для задачи идентификации радионуклидов по гамма-спектру.  

## Краткое описание задачи  
Алгоритм идентификации радионуклидов может быть применен в приборах - анализаторах спектра. Такие приборы, как правило, состоят из двух принципиальных составляющих - детектора и анализатора. Задача детектора - преобразовать данные, подлежащие анализу в цифровой вид. Задача анализатора - обработать данные детектора и сделать вывод об активности того или иного радионуклида.  
![image](https://user-images.githubusercontent.com/46919053/158963941-58377c34-1c08-4187-8722-ab4622e877bc.png)  

Объектом обоаботки явзяется гамма-спектр. Он представляет собой зависимость количества отсчетов от энергии. То есть какой-то массив, скажем, размера 1024, который обновляется с какой-то периодичностью, скажем, 1 раз в секунду. При этом обновляется он сложением новых значений с тем, что уже было (аккумулируется). Происходит набор статистики. Данные приходят в цифровом виде от детектора.  
Каждый нуклид обладает набором значений энергии и соответствующими энергиям интенсивностями. Эта информация известная, является справочной и хранится в так называемой библиотеке нуклидов. Задача обработки спектра состоит в том, чтобы найти энергии с максимальным счетом (по оси отсчетов) и проанализировать их на предмет соответствия с энергиями нуклидов. По результатом этого анализа можно сделать вывод о том, присутствует ли тот или иной нуклид в среде измерения. В текущей версии модели решается задача идентификации: то есть по спектру определяется радионуклид.  
![image](https://user-images.githubusercontent.com/46919053/158962522-e838375d-16da-4bb0-8fa0-135813dfa54e.png)  
  
## Описание ПО  
Программа состоит из двух виджетов.  
Первый - симуляция работы детектора. Можно сымитировать активность одного из 10 нуклидов, и увидеть соответствующий спектр. В фоновом режиме выполняется передача порций смоделированного спектра анализатору по протоколу UDP (клиенская часть). Также есть возможность геренации тестовых данных на основе реальных экспериментов. Тестовые данные представляют собой псевдо-рандомизированный массив размером, равным размеру спектра. Этот массив сформирован в зависимости от тренда спектра и параметра скорости счета: то есть представляет собой часть спектра, которая могла бы поступить на обработку от детектора за какой-то детерминированный период времени. В данном случае порции генерурются с периодом в 1 секунду.  
![image](https://user-images.githubusercontent.com/46919053/158976835-bb329b28-2d70-4f24-9d41-e354f9356121.png)  
Второй виджет - виджет анализатора. Отображает набранный спектр и результат его обработки: имя идентифицированного нуклида в поле "Activities" и энергии (из библиотеки нуклидов) в виде линий на соответствующих значениях по шкале энергий. Анализатор принимает данные по протоколу UDP (серверная часть), аккумулирует спектр, после каждого его обновленя подвергает обработке ML-модели.  
![image](https://user-images.githubusercontent.com/46919053/158976894-7a7c9498-9981-41bc-86fa-fb9cf0396dee.png)  
### Используемые технологии:  
- Qt 5.15.0
- Qwt 6.1.5 - Библиотека для построения графиков  
- TensorFlow - Обучение модели ML, имплементация модели (C-API, версия 2.7.0)  
- boost::asio - для работы с UDP-протоколом (версия 1.78)
- CMAKE - система сборки

## Архитектура ПО  
### Симулятор детектора  
![image](https://user-images.githubusercontent.com/46919053/163047518-357d6321-cac6-4195-aa0e-220835c2ace8.png)  
### Анализатор  
![image](https://user-images.githubusercontent.com/46919053/163047369-493d3d5d-8125-4701-b2c8-1f6bd96954fc.png)  

## Сверточная нейронная сеть  
### Архитектура  
![image](https://user-images.githubusercontent.com/46919053/158979617-d1c3ab5a-c3c5-4aa4-b8d0-bb24a4678d02.png)

### Процесс обучения  
Сформированы тестовые данные на основе имеющейся библиотеки нуклидов. Данные рандомизированы для различных соотношений сигнал-шум, разных интенсивностей, разного времени набора статистики: 
```matlab
possible_w = [0.025 0.05 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0];
possible_a = [0.025 0.05 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0];
possible_n = [1 2 3 4 5 6];
```
[Скрипт формирования тестовых данных](https://github.com/sanlav89/analyzer/blob/master/matlab/generate_train_data.m)  
Ниже приведен график процесса обучения. Точность модели получилась ~98.4 %  
![image](https://user-images.githubusercontent.com/46919053/158979874-959a90b7-c42a-462a-8396-cb7ff22dd1c6.png)

## TODO
- кросплатформенность: сборка проекта под Linux
- кросскомпиляция: сборка проекта кросскомпилятором ARM для исполнения на платформе Raspberry Pi 4
- совершенствование модели ML: расширение классов, задача идентификации и тд. 
