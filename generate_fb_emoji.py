import unicodecsv as csv
from wand.image import Image

emoji_positions = {}

with open('fb-emoji-positions.csv', 'rb') as posfile:
    posreader = csv.reader(posfile)
    for row in posreader:
        pos = row[2].split()
        emoji_positions[str(row[0])] = { 'file': row[1], 'x': -int(pos[0]), 'y': -int(pos[1]), 'w': 16, 'h': 16 }
        
img1 = Image(filename='fbicons.png')
img2 = Image(filename='fbicons2.png')

with open('fb-emoji-name2css.csv', 'rb') as namefile:
    namereader = csv.reader(namefile)
    for row in namereader:
        filepath = 'fb-emoji/{0}.png'.format(row[0])
        imgpos = emoji_positions[str(row[1])]
        if imgpos['file'] == 'fbicons.png':
            with img1[imgpos['x']:imgpos['x']+imgpos['w'], imgpos['y']:imgpos['y']+imgpos['h']] as chunk:
                chunk.save(filename=filepath)
        elif imgpos['file'] == 'fbicons2.png':
            with img2[imgpos['x']:imgpos['x']+imgpos['w'], imgpos['y']:imgpos['y']+imgpos['h']] as chunk:
                chunk.save(filename=filepath)
