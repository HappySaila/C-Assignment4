WLSGRA012 - Grant Wilson

HOW TO RUN THE PROGRAM.
Please take note that my make file will do everything for you.
You do not have to enter any commands yourself as the make file will do this for you.

You can perform the following using the make file:
Assuming I1 = "Lenna_hat_mask.pgm" and I2 = "Lenna_standard.pgm"
make add - will add I1 and I2
make sub - will subtract I1 and I2
make mask - will mask I2 using I1
make invert = will invert I1
make thresh = will thresh I1 with an f value of 120
make test - will run all of my test cases

Please note that after you use one of the above function, the make file will clean up after itself.
This prevents you from calling your own functions. So this should be really easy to mark.