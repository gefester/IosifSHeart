print("ПЕРЕВОДЧИК ТЕТРАМИНО В РЯД ЧИСЕЛ")
print("Правила заполнения ячеек:")
print("1. Сетка имеет размер сторого 4x4. Лишние символы будут отсекаться.")
print("2. Для обозначения заполненных ячейки используется цифры 1-3 (в зависимости от цвета). Для пустых - 0.")
print()

tetromino = []
rect = [3, 3, 0, 0]
for i in range(4):
    s = input()[:4]
    n = int(s, 4)
    tetromino.append(str(n))
print(", ".join(tetromino))

