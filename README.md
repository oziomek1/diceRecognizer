# diceRecognizer
(in the making) find and crop multi color dice image

Dice regoznizer using OpenCVs:
- cvtColor conversion to grayscale
- absdiff between to frames
- image segmentation by threshold - THRESH_OTSU and THRESH_BINARY
- edge detection using Canny algorithm ( Optimal detector )
- finding contours via RETR_EXTERNAL and CHAIN_APPROX_SIMPLE
- drawing rectangles