package perceptron

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type shape struct {
	number_of_examples int
	number_of_features int
	dimensions         int
}

type points struct {
	xcoord float64
	ycoord float64
	target int
}

type data struct {
	elements   [][]float64
	targets    []int
	dataPoints points
	dataShape  shape
}

type model struct {
	weights    []float32
	modelShape shape
}

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func newData(fname string) *data {
	datFile, err := os.Open(fname)
	number_of_example_lines := 0
	check(err)

	fileScanner := bufio.NewScanner(datFile)

	fileScanner.Split(bufio.ScanLines)

	for fileScanner.Scan() {
		number_of_example_lines++
	}

	data := data{}
	data.dataShape.number_of_examples = number_of_example_lines
	data.dataShape.number_of_features = 2

	datFile.Close()

	r := strings.NewReader("10 false GFG")

	n, err := fmt.Fscanf(r, "%d %t %s", &i, &b, &s)

	if err != nil {
		fmt.Fprintf(os.Stderr, "Fscanf: %v\n", err)
	}

	return &data
}
