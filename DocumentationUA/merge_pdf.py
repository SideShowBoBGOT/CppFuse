import os

names = [
    'Титульний лист',
    'Завдання та календарний план',
    'Анотація',
    'Пояснювальна записка без титулки',
    'Технічне завдання',
    'Опис програми',
    'Програма та методика тестування',
    'Керівництво користувача',
    'Відомість',
]

for name in names:
    os.system(f'libreoffice --headless --convert-to pdf \"{name}.odt\"')

cmd_names = " ".join(list(map(lambda name: '\"' + name + ".pdf\"", names)))
os.system(f'pdfunite {cmd_names} "КР_ІП-11_Панченко.pdf"')
