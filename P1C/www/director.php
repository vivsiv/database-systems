<?php
	include 'db_functions.php';
	if ($_GET["director_id"]){
		$db_connection = create_connection("localhost", "cs143", "");
		$director_id = intval(sanitize_string($_GET["director_id"], $db_connection));
		$director_base_query = "select * from Director where id=%d";
		$director_query = sprintf($director_base_query, $director_id);
		print $director_query . "<br/>";
		$director = run_query($director_query, $db_connection);

		$director_attr = mysql_fetch_array($director, MYSQL_ASSOC);
		print "<ul>";
		printf("<li>%s %s</li>", $director_attr["first"], $director_attr["last"]);
		printf("<li>%s</li>", $director_attr["dob"]);
		print "</ul>";
		print "<hr/>";

		$movie_director_base_query = "select mid from MovieDirector where did=%d";
		$movie_director_query = sprintf($movie_director_base_query, $director_id);
		print $movie_director_query . "<br/>";
		$movie_directors = run_query($movie_director_query, $db_connection);

		if (mysql_num_rows($movie_directors) > 0){
			$mids = array();
			while ($movie_director_row = mysql_fetch_array($movie_directors, MYSQL_ASSOC)){
				array_push($mids,$movie_director_row["mid"]);
			}
			$mid_string = implode(",",$mids);
			$movie_base_query = "select * from Movie where id in (%s)";
			$movie_query = sprintf($movie_base_query, $mid_string);
			print $movie_query . "<br/>";
			$movies = run_query($movie_query, $db_connection);

			print "<p>Movies..</p>";
			print "<ul>";
			while ($movie_row = mysql_fetch_array($movies, MYSQL_ASSOC)){
				printf("<li>%s (%s) Rated: %s</li>", $movie_row["title"], $movie_row["year"], $movie_row["rating"]);
			}
			print "</ul>";
			print "<hr/>";
		}
		close_connection($db_connection);
	}



?>