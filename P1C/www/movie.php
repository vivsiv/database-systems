<?php
	include 'db_functions.php';
	if ($_GET["movie_id"]){
		$db_connection = create_connection("localhost", "cs143", "");
		$movie_id = intval(sanitize_string($_GET["movie_id"], $db_connection));
		$movie_base_query = "select * from Movie where id=%d";
		$movie_query = sprintf($movie_base_query, $movie_id);
		print $movie_query . "<br/>";
		$movie = run_query($movie_query, $db_connection);

		$movie_attr = mysql_fetch_array($movie, MYSQL_ASSOC);
		print "<ul>";
		printf("<li>%s</li>", $movie_attr["title"]);
		printf("<li>%s</li>", $movie_attr["year"]);
		printf("<li>%s</li>", $movie_attr["rating"]);
		printf("<li>%s</li>", $movie_attr["company"]);
		print "</ul>";
		print "<hr/>";

		$movie_actor_base_query = "select aid from MovieActor where mid=%d";
		$movie_actor_query = sprintf($movie_actor_base_query, $movie_id);
		print $movie_actor_query . "<br/>";
		$movie_actors = run_query($movie_actor_query, $db_connection);

		if (mysql_num_rows($movie_actors) > 0){
			$aids = array();
			while ($movie_actor_row = mysql_fetch_array($movie_actors, MYSQL_ASSOC)){
				array_push($aids,$movie_actor_row['aid']);
			}
			$aid_string = implode(",",$aids);
			$actor_base_query = "select * from Actor where id in (%s)";
			$actor_query = sprintf($actor_base_query, $aid_string);
			print $actor_query . "<br/>";
			$actors = run_query($actor_query, $db_connection);

			print "<p>Actors..</p>";
			print "<ul>";
			while ($actor_row = mysql_fetch_array($actors, MYSQL_ASSOC)){
				printf("<li>%s %s</li>", $actor_row["first"], $actor_row["last"]);
			}
			print "</ul>";
			print "<hr/>";
		}
		
		$movie_director_base_query = "select did from MovieDirector where mid=%d";
		$movie_director_query = sprintf($movie_director_base_query, $movie_id);
		print $movie_director_query . "<br/>";
		$movie_directors = run_query($movie_director_query, $db_connection);

		if (mysql_num_rows($movie_directors) > 0){
			$dids = array();
			while ($movie_director_row = mysql_fetch_array($movie_directors, MYSQL_ASSOC)){
				array_push($dids, $movie_director_row['did']);
			}
			$did_string = implode(",",$dids);
			$director_base_query = "select * from Director where id in (%s)";
			$director_query = sprintf($director_base_query, $did_string);
			print $director_query . "<br/>";
			$directors = run_query($director_query, $db_connection);
			print "<p>Directors..</p>";
			print "<ul>";
			while ($director_row = mysql_fetch_array($directors, MYSQL_ASSOC)){
				printf("<li>%s %s</li>", $director_row["first"], $director_row["last"]);
			}
			print "</ul>";
			print "<hr/>";
		}
		close_connection($db_connection);
	}
?>