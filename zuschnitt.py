from PIL import Image
import glob, os

count = 0
image_list = []
basewidth = 100
size = (1903, 453)

for file in glob.iglob('D:\QTTest\GEO\Images\BROTHER\*.jpg'):
    im = Image.open(file)
    image_list.append(os.path.basename(file))
    width, height = im.size
    wpercent = (basewidth / float(im.size[0]))
    hsize = int((float(im.size[1]) * float(wpercent)))
    imCover = im.crop((0,0,width,((height*17)/19)))
   #    ((width - size[0]) // 2, (height - size[1]) // 2, (width + size[0]) // 2, (height + size[1]) // 2))
    imThumbnail = imCover.resize((basewidth, hsize), Image.LANCZOS)
    newCover = 'neu/{}'.format(image_list[count])
    newThumbnail = 'neu/{}_thumbnail.jpg'.format(image_list[count].replace(".jpg", ""))
    imCover.save(newCover, optimize=True, quality=85)
    imThumbnail.save(newThumbnail, optimize=True, quality=90)
    count += 1