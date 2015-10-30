<?php
	function create_connection($server_name, $login, $password){
		$db_connection = mysql_connect($server_name, $login, $password);
		if (!$db_connection){
			$error_msg = mysql_error($db_connection);
			print "<b>Database Connection Failed!</b><br/>";
			exit(1);
		}
		$db_selected = mysql_select_db("TEST", $db_connection);
		if (!$db_selected){
			print "<b>Database doesn't exist!</b><br/>";
			exit(1);
		}
		return $db_connection;
	}
		

	function choose_db($db_name, $db_connection){
		$db_selected = mysql_select_db($db_name, $db_connection);
		if (!$db_selected){
			print "<b>Database doesn't exist!</b><br/>";
			exit(1);
		}
		return $db_selected;
	}

	function sanitize_string($string, $db_connection){
		$sanitized = mysql_real_escape_string($string, $db_connection);
		if (!$sanitized){
			$error_msg = mysql_error($db_connection);
			print "<b>Database Error!</b> Please make sure the operation was valid.<br/>";
			exit(1);
		}
		return $sanitized;
	}

	function run_query($query, $db_connection){
		$result = mysql_query($query, $db_connection);
		if (!$result){
			$error_msg = mysql_error($db_connection);
			print "<b>Database Error!</b> Please make sure the operation was valid.<br/>";
			exit(1);
		}
		return $result;
	}

	function close_connection($db_connection){
		mysql_close($db_connection);
	}
?>