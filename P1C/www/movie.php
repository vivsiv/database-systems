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
			$url_safe_title = str_replace(" ", "+", $movie_attr["title"]);
			$movie_actor_link = sprintf("movie_actor_form.php?movie_id=%d&movie_title=%s", $movie_id ,$url_safe_title);
			print "<p><a href=$movie_actor_link>Add an Actor to this Movie</a></p>";

			print "<ul>";
			while ($actor_row = mysql_fetch_array($actors, MYSQL_ASSOC)){
				$actor_link = sprintf("actor.php?actor_id=%d", intval($actor_row['id']));
				printf("<li><a href=%s>%s %s</a></li>", $actor_link, $actor_row["first"], $actor_row["last"]);
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
			$url_safe_title = str_replace(" ", "+", $movie_attr["title"]);
			$movie_director_link = sprintf("movie_director_form.php?movie_id=%d&movie_title=%s", $movie_id ,$url_safe_title);
			print "<p><a href=$movie_director_link>Add a Director to this Movie</a></p>";

			print "<ul>";
			while ($director_row = mysql_fetch_array($directors, MYSQL_ASSOC)){
				$director_link = sprintf("director.php?director_id=%d", intval($director_row['id']));
				printf("<li><a href=%s>%s %s</a></li>", $director_link, $director_row["first"], $director_row["last"]);
			}
			print "</ul>";
			print "<hr/>";
		}

		$review_base_query = "select * from Review where mid=%d";
		$review_query = sprintf($review_base_query, $movie_id);
		print $review_query . "<br/>";
		$reviews = run_query($review_query, $db_connection);

		print "<p>Reviews...</p>";
		$url_safe_title = str_replace(" ", "+", $movie_attr["title"]);
		$review_link = sprintf("review_form.php?movie_id=%d&movie_title=%s", $movie_id, $url_safe_title);
		print "<p><a href=$review_link>Create a review for this Movie</a></p>";
		if (mysql_num_rows($reviews) > 0){
			while ($review_row = mysql_fetch_array($reviews, MYSQL_ASSOC)){
				print "<ul>";
				printf("<li>%d Stars, %s, %s</li>", $review_row["rating"], $review_row["name"], $review_row["time"]);
				printf("<li>%s</li>", $review_row["comment"]);
				print "</ul>";
			}
		}
		else {
			print "<p>Be the first to write a review!</p>";
		}
		print "<hr/>";
		close_connection($db_connection);
	}
?>