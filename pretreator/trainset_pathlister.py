import os

class TrainSetPathsCreator:
    def __init__(self, dir='/home/chunwei/NetFlixData/training_set/', tofile='/home/chunwei/NetFlixData/trainset_paths.red'):
        self._dir = dir
        self._tofile = tofile

    def parse(self):
        '''
        main program
        '''
        self.tofile()

    def load(self):
        files = os.listdir(self._dir)
        for f in files:
            path = os.path.join(self._dir, f)
            yield path

    def tofile(self):
        strr = ''
        for path in self.load():
            strr += path + '\n'
        f = open(self._tofile, 'w')
        f.write(strr)
        f.close()

if __name__ == '__main__':
    p = TrainSetPathsCreator()
    p.parse()


