# Digit Recognizer in C

A from-scratch C project exploring how a neural network can learn to recognize handwritten digits from **0 to 9**.

## Project goal

I’m building this as an introduction to machine learning. The goal is to understand what happens inside a neural network by implementing the main pieces in C: loading digit images, converting pixels into numbers, doing matrix operations, and eventually training and evaluating a model.

## Progress

This project is a work in progress. I’m currently working on reading image pixels and building the matrix operations needed by the network. Training and evaluation are planned next.

## Planned steps

- Load 28 × 28 grayscale digit images.
- Convert each image into a vector of pixel values and normalize them.
- Implement the network’s forward pass.
- Add a loss function and backpropagation.
- Train and evaluate the model on labeled digits from 0 to 9.

## Learning resources

I’m using these resources while building the project:

- [Neural Networks and Deep Learning](http://neuralnetworksanddeeplearning.com/) by Michael Nielsen — a guide to the ideas and math behind neural networks.
- [3Blue1Brown’s neural networks series](https://www.youtube.com/watch?v=IHZwWFHWa-w&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi&index=3) — visual explanations of how neural networks work and learn.

## Build

The project uses [`stb_image`](https://github.com/nothings/stb) to load PNG images. Keep `stb_image.h` beside `checker.c`.

```sh
cc checker.c -o checker -lm
```

`-lm` links the C math library used by the sigmoid calculation.

## Dataset and attribution

The handwritten digit data is based on the [MNIST database](https://keras.io/api/datasets/mnist/), created by Yann LeCun and Corinna Cortes. Keras lists MNIST under the **Creative Commons Attribution-ShareAlike 3.0** license.

The PNG-converted copy used during development came from [Morais Lyra Junior’s Zenodo record](https://doi.org/10.5281/zenodo.13292895). That record does not currently display a license for the converted archive, so the image dataset is not included in this repository. Check the source’s terms before redistributing those files.

## Acknowledgements

- Yann LeCun and Corinna Cortes for the MNIST handwritten digit database.
- Sean Barrett and the contributors to [`stb_image`](https://github.com/nothings/stb) for the image-loading header.
