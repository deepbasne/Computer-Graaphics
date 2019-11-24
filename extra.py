from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
from random import randint
from time import time

output_file = "output.png"

# Code sample taken from github
#Worked my way through setting up the system
#I ran it in my system not sure but running it took me like 6-7 hrs just to create an image of 256*256
#Then I used the provided image to get a 160*160 image 
#system info: windows 8.1, VS code, python 3.7, 2.16GHz, 4 GB ram

def process_pixel(x, y, img_data, new_img_data, mask, kernel_size):

    x0 = max(0, x - kernel_size)
    y0 = max(0, y - kernel_size) 
    x1 = min(new_img_data.shape[0] - 1, x + kernel_size)
    y1 = min(new_img_data.shape[1] - 1, y + kernel_size)

    neigh_window = new_img_data[int(x0) : int(x1), int(y0) : int(y1)]

    mask_window = mask[int(x0) : int(x1), int(y0) : int(y1)]
    len_mask = float(len(mask_window==True))

    xs, ys = neigh_window.shape
    img_xsize, img_ysize = img_data.shape

    cx = int(np.floor(xs/2))
    cy = int(np.floor(ys/2))

    candidates = []
    dists = []

    for i in range(xs, img_xsize - xs):
        for j in range(ys, img_ysize - ys):
            if(randint(0,2) != 0): continue
            sub_window = img_data[i : i+xs, j : j+ys]

            # distance
            s = (sub_window - neigh_window)

            summ = s*s*mask_window

            d = np.sum(summ) / len_mask

            candidates.append(sub_window[cx, cy])
            dists.append(d)

    mask = dists - np.min(dists) < 0.2

    candidates = np.extract(mask, candidates)   

    # pick random among candidates
    if len(candidates) < 1:
        return 0.0
    else:
        if len(candidates) != 1:
            r = randint(0, len(candidates) - 1)
        else:
            r = 0

    return candidates[r]

    

def efros(img_data, new_size_x, new_size_y, kernel_size, t):

    patch_size_x, patch_size_y = img.size 
    size_seed_x = size_seed_y = 3

    seed_x = randint(0, size_seed_x)
    seed_y = randint(0, size_seed_y)

    # take 3x3 start image (seed) in the original image
    seed_data = img_data[seed_x : seed_x + size_seed_x, seed_y : seed_y + size_seed_y]

    new_image_data = np.zeros((new_size_x, new_size_y))
    mask = np.ones((new_size_x, new_size_y)) == False

    mask[0: size_seed_x, 0: size_seed_y] = True

    new_image_data[0: size_seed_x, 0: size_seed_y] = seed_data


    # TO DO: non-square images

    it = 0
    for i in range(size_seed_x, new_size_x ):

        print('Process ', i, ' / ', new_size_x, '. Time: ', time() - t, ' seconds')
        last_y = size_seed_x + it
        # xxxxxxx
        for j in range(0, last_y + 1):

            v = process_pixel(i, j, img_data, new_image_data, mask, kernel_size)

            new_image_data[i, j] = v
            mask[i, j] = True
            

        # x
        # x
        # x
        for x in range(0, size_seed_y + it + 1):

            v = process_pixel(x, last_y, img_data, new_image_data, mask, kernel_size)

            new_image_data[x, last_y] = v
            mask[x, last_y] = True

        it += 1


        if(it % 10 == 0) :
            img_new = Image.fromarray(new_image_data)
            img_new.convert("RGB").save(output_file)


    return img_new

# main program

filename = "input.png"
new_size_x = 160
new_size_y = 160
kernel_size = 21

img = Image.open(filename)
img_data = img.convert("L")
img_data = np.array(img_data)

print('Starting...')

t = time()

img_new = efros(img_data, new_size_x, new_size_y, kernel_size/2, t)

print('Total Time: ', time() - t, ' seconds')

print('Finished!')

plt.imshow(img_new, cmap = "Greys")
plt.show()


img_new.convert("RGB").save(output_file)

