<?php
	include 'db_functions.php';
	if($_GET["create_movie_person"]) {
		$db_connection = create_connection("localhost", "cs143", "");
		$person_type = sanitize_string($_GET["create_movie_person_select"], $db_connection);

		$person_name = sanitize_string($_GET["person_name"], $db_connection);
		$first = explode(" ", $person_name)[0];
		$last = explode(" ", $person_name)[1];
		$person_table_name = ucfirst($person_type);
		print $table_name . "<br/>";
		$person_base_query = "select id,first,last from $person_table_name where first='%s' and last='%s' limit 1";
		$person_query = sprintf($person_base_query, $first, $last);
		print $person_query . "<br/>";
		$person = run_query($person_query, $db_connection);


		$movie_title = sanitize_string($_GET["movie_title"], $db_connection);
		$movie_base_query = "select id,title from Movie where title='%s' limit 1";
		$movie_query = sprintf($movie_base_query, $movie_title);
		print $movie_query . "<br/>";
		$movie = run_query($movie_query, $db_connection);

		$role = NULL;
		if ($_GET["role"]){
			$role = sanitize_string($_GET["role"], $db_connection);
		}
		

		print "<p>Person Found</p>";
		$person_row = mysql_fetch_array($person, MYSQL_ASSOC);
		printf("<p>%d %s %s</p>", $person_row['id'], $person_row['first'], $person_row['last']);
		$person_id = $person_row['id'];

		print "<p>Movie Found</p>";
		$movie_row = mysql_fetch_array($movie, MYSQL_ASSOC);
		printf("<p>%d %s</p>", $movie_row['id'], $movie_row['title']);
		$movie_id = $movie_row['id'];

		$movie_person_table_name = NULL;
		if ($person_type == "actor") $movie_person_table_name = "MovieActor";
		else $movie_person_table_name = "MovieDirector";
		$movie_person_base_query = "insert into $movie_person_table_name values (%d,%d";
		if ($person_type == "actor") $movie_person_base_query .= ",'%s')";
		else $movie_person_base_query .= ")";

		$movie_person_query = sprintf($movie_person_base_query, $movie_id, $person_id);
		if ($person_type == 'actor') {
			$movie_person_query = sprintf($movie_person_base_query, $movie_id, $person_id, $role);
		}
		print $movie_person_query . "<br/>";
		run_query($movie_person_query, $db_connection);

		close_connection($db_connection);
	}
?>