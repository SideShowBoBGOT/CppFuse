import os
with open('./code.txt', 'w') as output:
    for dir in ["../Source", "../External/RwLock/Include"]:
        for root, dirs, files in os.walk(dir):
            for file in files:
                if file.endswith('.hpp') or file.endswith('.cpp'):
                    path = root + os.sep + file
                    output.write('// ' + path + '\n\n')
                    with open(path, 'r') as ff:
                        output.write(''.join(ff.readlines()))
                    output.write('\n\n')
            
