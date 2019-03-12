package main;
type a int
type b a
type c b
type d []int
type e []c
type f [1]e
type p struct {
	q int
	i c
}

type (
	pp struct{
		ll int
	}
)
func main(){
	var g c;
}
