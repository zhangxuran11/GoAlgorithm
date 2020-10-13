// test project main.go
package main

import (
	"fmt"
)

func insertSort(arr []int) {
	for i := 0; i < len(arr); i++ {
		for j := i; j > 0 && arr[j] < arr[j-1]; j-- {
			arr[j], arr[j-1] = arr[j-1], arr[j]
		}
	}
}
func shellSort(arr []int) {
	for dk := len(arr) / 2; dk > 0; dk /= 2 {
		for i := 0; i < dk; i++ {
			for j := i; j < len(arr); j += dk {
				for k := j; k >= dk && arr[k] < arr[k-dk]; k -= dk {
					arr[k-dk], arr[k] = arr[k], arr[k-dk]
				}
			}
		}
	}
}
func binarySort(arr []int) {
	for i := 0; i < len(arr); i++ {
		left, right := 0, i-1
		for left <= right {
			mid := (right + left) / 2
			if arr[i] < arr[mid] {
				right = mid - 1
			} else {
				left = mid + 1
			}
		}
		tmp := arr[i]
		for j := i; j > left; j-- {
			arr[j] = arr[j-1]
		}
		arr[left] = tmp
	}
}

func bubblingSort(arr []int) {
	for i := len(arr) - 1; i > 0; i-- {
		for j := 0; j < i; j++ {
			if arr[j] > arr[j+1] {
				arr[j], arr[j+1] = arr[j+1], arr[j]
			}
		}
	}
}

//归并
func merge(arr1, arr2 []int) []int {

	arr := make([]int, len(arr1)+len(arr2))
	i, j, k := 0, 0, 0
	for i < len(arr1) && j < len(arr2) {
		if arr1[i] <= arr2[j] {
			arr[k] = arr1[i]
			k++
			i++
		} else {
			arr[k] = arr2[j]
			k++
			j++
		}
	}
	if i >= len(arr1) {
		copy(arr[k:], arr2[j:])
		k += len(arr2) - j
		j = len(arr2) - 1
	} else {
		copy(arr[k:], arr1[i:])
		k += len(arr1) - i
		i = len(arr1) - 1
	}
	return arr
}

func mergeSort(arr []int) []int {
	if len(arr) <= 1 {
		return arr
	}
	mid := len(arr) / 2
	left := mergeSort(arr[:mid])
	right := mergeSort(arr[mid:])
	return merge(left, right)
}

//快速
func quickSort(arr []int) []int {
	if len(arr) <= 1 {
		return arr
	}
	left, right := make([]int, len(arr)), make([]int, len(arr))
	j, k := 0, 0
	for i := 1; i < len(arr); i++ {
		if arr[i] < arr[0] {
			left[j] = arr[i]
			j++
		} else {
			right[k] = arr[i]
			k++
		}
	}
	copy(left[:j], quickSort(left[:j]))
	left[j] = arr[0]
	j++
	copy(left[j:], quickSort(right[:k]))
	return left
}

func binarySearch(arr []int, val int) int {
	left, right := 0, len(arr)-1
	for left <= right {
		mid := (left + right) / 2
		if val == arr[mid] {
			return mid
		} else if val < arr[mid] {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}
	return -1
}

func main() {
	fmt.Println("Hello World!")
	rawInt := []int{7, 6, 9, 3, 1, 5, 2, 4}

	arr := make([]int, len(rawInt))
	copy(arr, rawInt)
	fmt.Println(arr)
	insertSort(arr)
	fmt.Println("insertSort", arr)

	copy(arr, rawInt)
	fmt.Println(arr)
	shellSort(arr)
	fmt.Println("shellSort", arr)

	copy(arr, rawInt)
	fmt.Println(arr)
	binarySort(arr)
	fmt.Println("binarySort", arr)

	copy(arr, rawInt)
	fmt.Println(arr)
	bubblingSort(arr)
	fmt.Println("bubblingSort", arr)

	copy(arr, rawInt)
	fmt.Println(arr)
	arr = mergeSort(arr)
	fmt.Println("mergeSort", arr)

	copy(arr, rawInt)
	fmt.Println(arr)
	arr = quickSort(arr)
	fmt.Println("quickSort", arr)

	fmt.Println(binarySearch(arr, 9))
	fmt.Println(binarySearch(arr, 7))
	fmt.Println(binarySearch(arr, 3))
}
