package main

// var a = 10
// var b int
// var c1 bool
// var c2 rune
// var c3 string
// var c4 float64
// var (
// 	d       = 10
// 	e       = 3.32
// 	g, h, i int
// )
// var j, k, l = 10, 20, 30
// var m [5]int
// var ms [5]string
// var n []float64
// var nb [][]float64
// var mss [5][5]int
// var msss [][5]int
// var mssss [5][]int
// var sss [1][][][5][][5][]int
type sl [5][5]int
type sss []sl

var l sl
var d []sss

// type b struct {
// 	c, g, h int
// 	d       float64
// 	k       [5][]int
// }

// var a b
func main() {
	var slice []int
	slice = append(slice, 101)
	print(slice[0])
	print("\n")
}
