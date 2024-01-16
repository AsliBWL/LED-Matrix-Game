Игра на светодиодной матрице

Суть игры

Человек на светодиодной матрице должен преодолевать препятствия; если человек наталкивается на препятствие, игра заканчивается; должно быть 2 кнопки, первая – для передвижения человека вверх, вторая – для ускорения движения человека вправо. 

Необходимое оборудование:

1) светодиодная матрица P10;
2) отладочная плата STM32F411E-DISCO;
3) блок питания, который выдает напряжения 5 В;
4) 2 тактовые кнопки.

Создание игры

Сборка электрической цепи

1) В соответствии с обозначениями (VCC, GND) подключаем светодиодную матрицу к блоку питания, который дает 5 В, как показано на рисунке 1 (красный прямоугольник).

![image](https://github.com/AsliBWL/LED-Matrix-Game/assets/156215350/3d7f160b-0ab5-40e6-bb18-6504897b8d05)

Рисунок 1 – Светодиодная матрица с обратной стороны

2) Подключаем светодиодную матрицу к отладочной плате через входной интерфейсный разъем на матрице (рисунок 1 (синий прямоугольник)), распиновка которого представлена на рисунке 2, в соответствии с таблицей 1.

![image](https://github.com/AsliBWL/LED-Matrix-Game/assets/156215350/f87ee1a3-e640-4df9-8d3a-6fc543b4dd05)

Рисунок 2 – Распиновка входного интерфейсного разъема светодиодной матрицы

Таблица 1 – Пины входного интерфейсного разъема светодиодной матрицы и отладочной платы, которые необходимо подключить друг к другу

![таблица](https://github.com/AsliBWL/LED-Matrix-Game/assets/156215350/358de69a-895f-420e-bfa3-329d6e95339e)

3) Подключаем две тактовые кнопки к отладочной плате согласно таблице 2.

Таблица 2 – Подключение тактовых кнопок к отладочной плате

![таблица3](https://github.com/AsliBWL/LED-Matrix-Game/assets/156215350/2b7b206c-4162-4044-8d07-c51f7c930a89)

Создание стартового проекта в среде STM32CubeIDE

1) В среде STM32CubeMX был создан начальный конфигурационный проект.

   1.1) System Core:
   
        RCC → HSE – Crystal/Ceramic Resonator
   
        SYS → Debug – Serial Wire
   
   1.2)	Timers:
   
         TIM2:
   
         Clock Source – Internal Clock
   
         Channel1 – Output Compare No Output
   
         PSC = 25000 – 1
   
         Counter Mode – Up
   
         ARR = 1000 – 1
   
         NVIC Settings → TIM2 global interrupt → Enabled – галочка
   
         Расчет значения регистра предделителя (Prescaler (PSC)) и периода таймера (Counter Period (AutoReload Register (ARR))) для TIM2:
   
         M = 50 МГц – тактовая частота шины (APB1), с которой подается тактовый сигнал на таймер TIM2.
   
         f – частота, с которой таймер должен генерировать прерывания.

         ![формулы](https://github.com/AsliBWL/LED-Matrix-Game/assets/156215350/fc60c2cf-cf48-425b-90ea-76784aab3210)

         Подберем значения PSC и ARR: PSC = 25000 – 1; ARR = 1000 – 1.
   
   1.3) Настройка SPI-интерфейса
   
        Connectivity → SPI2:
   
        Mode – Transmit Only Master
   
        Data Size = 8 Bits
   
        Prescaler = 4

2) Определяем пины на микроконтроллере для подключения светодиодной матрицы и кнопок (таблица 2).

Таблица 2 – Таблица задействованных портов GPIO 

![таблица2](https://github.com/AsliBWL/LED-Matrix-Game/assets/156215350/f237d90b-425a-4e54-a56e-dbbf152999b1)

![image](https://github.com/AsliBWL/LED-Matrix-Game/assets/156215350/a792677a-ffcf-4106-8188-f67d297996ca)

Рисунок 3 – Задействованные пины микроконтроллера

Написание кода ПО

После создания стартового проекта в среде STM32CubeIDE необходимо загрузить в папку проекта файлы P10.h (папка проекта -> Core -> Inc) и P10.c (папка проекта -> Core -> Src). Также необходимо, чтобы в файле main.c был код из одноименного файла, прикрепленного к данному описанию, а в файле stm32f4xx_it.c - код из одноименного файла, который также прикреплен к данному описанию. Следует отметить, что функции FillPixelX и FillPixelY необходимы для того, чтобы инициализировать координаты светодиодов горизонтальной и вертикальной линий соответственно, которые должны входить в состав дороги на светодиодной матрице.

Все переменные, используемые в ПО, описаны в файле "Таблица переменных", который прикреплен к данному описанию.
