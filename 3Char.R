library(hash)

#this function will be used to count all of the three character
#occurences for a given string
ThreeCharCount <- function(string)
{
	dict = hash()
	dict$size = nchar(string) -2;
	
	#split up string into vector for quick individual acces
	vector = strsplit(gsub("([[:alnum:]]{1})", "\\1", string), "")[[1]]
	
	#create a vector to hold the memory for each threeChar string
	threeChar = c()
	
	#use i to keep track of place in for loop
	i = 1
	for(char in vector)
	{
		#visual book keeping
		if(i%%10000 == 0)
		{
			print(i)
		}
		
		#iterate through the first three characters and append them
		#to initially empty "threeChar" before writing to the dictionary
		threeChar <- paste(threeChar, char, sep="")
		i = i + 1
		if(i>3)
		{
			#lookup threeChar for existence in dict
			if(!is.null(dict[[threeChar]]))
			{
				#if exists, increment threeChar key-value
				dict[[threeChar]] <- (dict[[threeChar]] +1)
			}
			else
			{
				#otherwise create new key-value pair
				dict[[threeChar]] <- 1
			}
			#remove the first letter of the threeChar to maintain three characters
			threeChar <- substr(threeChar, 2, 3)
		}
	}
	return (dict)
}

#this function will be used to add two "dicts" together and
#their key-value pairs
ThreeCharAdd <- function(a, b)
{
	for(string in names(a))
	{
		if(string %in% names(b))
		{
			b[[string]] = (b[[string]] + a[[string]])
		}
		else
		{
			b[[string]] = a[[string]]
		}
	}
	return (b)
}

CountForAllIds <- function(table)
{
	print("hello")
	set = c()
	for(i in 1:(length(table$V1)))
	{
		print(i)
		index <- toString(table$V2)
		if(index %in% names(set) )
		{
			print("CountForAllIds, inside if statement")
			tempDict <- ThreeCharCount(toString(table$V3[i]))
			set[[index]] <- ThreeCharAdd(set[[index]], tempDict)
		}
		else
		{
			print("inside else statement")
			set[[index]] <- ThreeCharCount(toString(table$V3[i]))
		}
	}
	return (set)
}