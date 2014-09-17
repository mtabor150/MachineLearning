library(hash)

#this function will be used to count all of the three character
#occurences for a given string
ThreeCharCount <- function(string, dict=NULL)
{
	if(is.null(dict))
	{
	  dict = hash()	
	}
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
		if(!is.null(b[[string]]))
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

#This function is used strictly for a specific data Table type
#and is incomplete
#only meant to be used for the 
CountForAllIds <- function(table)
{
	list = list()
	names = list()
	for(i in 1:(length(table$V1)))
	{
		index <- toString(table$V2[i])
		if(index %in% names(names))
		{
			set <- list[[index]]
			set <- ThreeCharCount(toString(table$V3[i]), dict=set)
		}
		else
		{
			names[[index]] = 0
			set <- hash()
			set <- ThreeCharCount(toString(table$V3[i]), dict=set)
			list[[index]] <- set
		}
	}
	return (list)
}

#returns the cosine of the angle between two vectors
#uses dot product formula
VectorAngDist <- function( dictA, dictB)
{
	dist <-0.0
	magnitude = Magnitude(dictA)*Magnitude(dictB)
	for(key in names(dictA))
	{
		if(!is.null(dictB[[key]]))
		{
			dist = dist + (dictB[[key]] * dictA[[key]])
		}
	}
	return (dist/magnitude)
}

#returns the magnitude of a vector
Magnitude <- function(dict)
{
	value <-0
	for(key in names(dict))
	{
		tempVal = dict[[key]]
		value = value + tempVal*tempVal
	}
	return (sqrt(value))
}

#returns a matrix of the cos(angle) between all of the vectors in a dict
VADList <- function(dict)
{
	list = c()
	for(key1 in names(dict))
	{
		vector1 = dict[[key1]]
		for(key2 in names(dict))
		{
			vector2 = dict[[key2]]
			distance = VAngle(vector1, vector2)
			list = c(list, distance)
		}
	}
	return (list)
}

#This function takes 2 "dicts" and returns the euclidean distance
EDist <- function (dicta, dictb)
{
  dist = 0;
  for(key in names(dicta))
  {
    valueOfKeyInDictA = dicta[[key]]
    if(!is.null(dictb[[key]]))
    {
      valueOfKeyInDictB = dictb[[key]]
      dist = dist+((valueOfKeyInDictA-valueOfKeyInDictB)^2)
    }
    else
    {
      dist = dist+(valueOfKeyInDictA^2)
    }
  }
  
  for(key in names(dictb))
  {
    valueOfKeyInDictB = dictb[[key]]
    if(is.null(dicta[[key]]))
    {
      dist = dist+(valueOfKeyInDictB^2)
    }
  }
  
  dist = sqrt(dist)
  return (dist)
}

#This function takes 2 "dicts" and returns the angle between them
VAngle <- function (dicta, dictb)
{
  norma = 0
  adotb = 0
  for(key in names(dicta))
  {
    norma = norma + (dicta[[key]]^2)
    if(!is.null(dictb[[key]]))
    {
      adotb = adotb + (dicta[[key]]*dictb[[key]])
    }
  }
  norma = sqrt(norma)
  
  normb = 0
  for(key in names(dictb))
  {
    normb = normb + (dictb[[key]]^2)
  }
  normb = sqrt(normb)

  if(norma > 0 && normb > 0)
  {
  angle = adotb/(norma*normb)
  angle = acos(angle)*(180/pi)
  return (angle)
  }
  else
  {
  	return (-1)
  }
}