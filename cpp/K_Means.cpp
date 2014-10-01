/* 
 * copyright 2014, Phillip Martin
 * K_Means.cpp provides functionality to cluster
 * a set of vectors based on their angular proximity to each other
 */

#include <iostream>
#include <map>
#include <cmath>

#include "Twitter_Count.h"
#include "Three_Char_Vector.h"

using namespace std;

struct cluster
{
	three_char_vector centroid;
	vector_map cluster_points;
};

struct uid_dist
{
	int user_id;
	int dist;
};

typedef map<int,cluster> cluster_group;

//find_proximity_vector will find either the furthest vector in
//map from user_id or the closest one, depending on the flag "findFurthest"
//
//Note: if user_id is in the map, zero will be returned if looking
//      for the minimum distance.
uid_dist find_proximity_vector(vector_map *map, three_char_vector *user_vect, bool findFurthest)
{
	double return_dist;
	if(findFurthest)
	{
		return_dist = 0.0;
	}
	else//else looking for minimum dist
	{
		return_dist = 90.0;
	}
	three_char_vector other_vector;
	int return_user = -1;
	
	//iterate through the map to find the furthest/closest distance
	double temp_dist;
	vector_map::iterator iter;
	for(iter=map->begin(); iter!=map->end(); iter++)
	{
		temp_dist = VAngle(user_vect, &iter->second);

		//if findFurthest is true and temp_dist is greater
		//than return_dist, then we want to update return_dist.
		//Contrarily, if findFurthest is false and temp_dist
		//is less than return_dist, the we also want to update
		//return_dist.
		if(( findFurthest && (temp_dist > return_dist) )
	    || ( !findFurthest && (temp_dist < return_dist) ))
		{
			return_dist = temp_dist;
			return_user = iter->first;
		}
	}
	struct uid_dist return_uid_dist;
	return_uid_dist.user_id = return_user;
	return_uid_dist.dist = return_dist;
	return return_uid_dist;
}

//finds furthest vector in map from that of user_id
int find_furthest_vector(vector_map *map, three_char_vector *user_vect)
{
	bool find_furthest_vector = true;//yes finding furthest
	return find_proximity_vector(map,user_vect,find_furthest_vector).user_id;
}

//finds the distance between user_id and the furthest vector
double find_furthest_dist(vector_map *map, three_char_vector *user_vect)
{
	//compute the distance between the furthest vector and user_id
	return find_proximity_vector(map,user_vect, true).dist;
}

//finds the closest vector in map to that of user_id
int find_closest_vector(vector_map *map, three_char_vector *user_vect)
{
	bool find_furthest_vector = false;//no not finding furthest
	return find_proximity_vector(map,user_vect,find_furthest_vector).user_id;
}

//finds the distance between user_id and the closest vector in a vector map
double find_closest_dist(vector_map *map, three_char_vector *user_vect)
{
	//compute the distance between the closest vector and user_id
	return find_proximity_vector(map,user_vect,false).dist;
}

//this function will find the closest cluster in a clusters to vect
int find_closest_cluster(cluster_group *clusters, three_char_vector *vect)
{
	//convert the clusters to a vector map of centroids
	vector_map cluster_map;
	int clusters_size = clusters->size();
	for(int i = 0; i< clusters->size(); i++)
	{
		cluster_map[i] = (*clusters)[i].centroid;
	}

	//return the index of the closest vector in cluster_map to vect
	return find_closest_vector(&cluster_map, vect);
}


//finds the vector in the map which has the largest minimum distance from
//the vectors in centroids
int find_furthest_minimum(vector_map *centroids, vector_map *map)
{
	double furthest_dist = 0.0;
	double min_user_dist;
	int return_user=-1;

	//iterate through the map finding the minimum distance
	//to the centroids for each user
	vector_map::iterator iter;
	for(iter = map->begin(); iter!=map->end(); iter++)
	{
		min_user_dist = find_closest_dist(centroids, &iter->second);
		if(min_user_dist > furthest_dist)
		{
			furthest_dist = min_user_dist;
			return_user = iter->first;
		}
		
	}
	return return_user;
}

//this will return a vector_map of k centroids quasi-maximally spaced apart
vector_map first_k_centroids(vector_map *map, int k )
{
	//centroids will keep track of the centroids
	vector_map centroids = vector_map();
	centroids[map->begin()->first] = map->begin()->second;

	//find the furthest minimum from the centroids k times
	int new_centroid;
	for(int i = 0; i< k-1 ; i++)
	{

		new_centroid = find_furthest_minimum(&centroids, map);
		centroids[-i] = (*map)[new_centroid];
	}
	return centroids;
}


void print_clusters(cluster_group *group)
{
	cout << "-------------------------------------------------------------------------" << endl;
	int size = group->size();
	for(int i=0; i<size; i++)
	{
		cout << "group " << i << ":" <<endl;
		print_all_ids(&(*group)[i].cluster_points);
		print_all_distances(&(*group)[i].cluster_points);
	}
}

double average_dist_from_centroids(cluster_group *group)
{
	double return_dist = 0.0;
	int num_vects = 0;

	//iterate through cluster_group
	int size = group->size();
	for(int i=0; i<size; i++)
	{
		//iterate through vector_map
		double temp_dist;
		cluster clust = (*group)[i];
		three_char_vector centroid = clust.centroid;
		vector_map map = clust.cluster_points;
		vector_map::iterator iter;
		for(iter=map.begin(); iter!=map.end(); ++iter)
		{
			num_vects++;
			temp_dist = VAngle(&centroid, &iter->second);
			return_dist += temp_dist;
		}
	}

	return return_dist/num_vects;
}

cluster_group k_means_cluster(vector_map *map, int k)
{
	vector_map centroids = first_k_centroids(map, k);
	cluster_group clusters = cluster_group();

	//place centroid vectors into cluster group as the centroids
	int i =0;
	vector_map::iterator c_iter;
	for(c_iter = centroids.begin(); c_iter!=centroids.end(); ++c_iter)
	{
		clusters[i] = cluster();
		clusters[i].centroid = c_iter->second;
		i++;
	}

	bool still_changing = true;
	int iteration = 0;
	while(still_changing)
	{
		iteration++;
		//cout << "iteration " << iteration << endl;
		//iterate through map and place each elements into closest cluster
		int closest_clust;
		vector_map::iterator m_iter;
		for(m_iter = map->begin(); m_iter!=map->end(); ++m_iter)
		{
			//find closest centroid to element
			closest_clust = find_closest_cluster(&clusters, &m_iter->second);
			clusters[closest_clust].cluster_points[m_iter->first] = m_iter->second;
		}

		//average out all of the clusters
		for(i = 0; i< k ; i++)
		{
			three_char_vector average = average_vector(&clusters[i].cluster_points);
			if(three_char_vector_equal(&clusters[i].centroid, &average))
			{
				clusters[i].centroid = average;
				clusters[i].cluster_points = vector_map();
			}
			else
			{
				still_changing = false;
			}
		}

	}

	//for each cluster find a new average centroid
	cout << "===========================================" << endl;
	cout << "final iteratrion:" << endl;
	//print_clusters(clusters);
	cout << "number of centroids: " << k << endl;
	cout << "average distance from centroid: " << average_dist_from_centroids(&clusters)<< endl;
	cout << "===========================================" << endl;
	return clusters;
}





int main()
{
	vector_map vect_map = vector_map();

	vect_map = vector_map_constructor("../twitter_text/bar-tweets.txt");

	write_vector_map_to_file(&vect_map, "bavarian-tweets-vectors/");

	cout << "ada" << endl;
	ifstream t("../twitter_text/MobyDick.txt");
	string str;

	t.seekg(0, ios::end);   
	str.reserve(t.tellg());
	t.seekg(0, ios::beg);

	str.assign((istreambuf_iterator<char>(t)),
	            istreambuf_iterator<char>());
	struct three_char_vector count3;
	count3 = three_char_count(str);
	
	vect_map[1] = count3;

	print_all_ids(&vect_map);
	print_all_distances(&vect_map);

	/*
	for(int i = 1; i<20; i++)
	{
	cluster_group group = k_means_cluster(&vect_map, i);
	}
	*/

	return 0;
}