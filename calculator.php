<h1>Calculator</h1>
<p>by Vivek Sivakumar</p>
<br/>

<p>
<form action="calculator.php" method="GET">
	<input type="text" name="expr">
	<input type="submit" value="Calculate">
</form>
</p>

<?php
	if($_GET["expr"]){
		$expr = $_GET["expr"];
		// echo "expr: " . $expr;
		// echo "<br/>";
		$validExprRegex = '/(([-]?\d+([.]?\d+)?)[\+\-\*\/])*([-]?\d+([.]?\d+)?)/';
		preg_match($validExprRegex, $expr, $exprMatches);
		// echo "exprMatches[0]: " . $exprMatches[0];
		// echo "<br/>";
		$validExpr = $exprMatches[0];
		if ($validExpr && strlen($validExpr) == strlen($expr)){
			$divideByZeroRegex = "/(\/0)/";
			preg_match($divideByZeroRegex, $validExpr, $divideMatches);
			$divideByZeroError = $divideMatches[0];
			if ($divideByZeroError){
				echo "Divide by zero error!";
			}
			else {
				eval("\$answer = $expr;");
				echo $expr . " = " . $answer;
			}	
		}
		else {
			echo "Invalid Expression!";
		}
	}
	else {
		echo "Nothing to calculate";
	}

?>