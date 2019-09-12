<?php 
	require('connexion.php'); //Permet la connexion à la base de données
	require('debut.php'); //En-tête html
	require('fonctions.php'); //Ensemble de fonctions PHP
?>

<?php

	$scores = scoreMaxMoyen($bd);

?>


<div class="resultat">
	<p>Meilleurs joueurs d'échecs au monde (ayant atteint le score <?php echo $scores['max']; ?>) :</p>
	<?php afficheJoueursScore($bd,$scores['max']); ?>

	<p>Score moyen au classement ELO : <?php echo $scores['avg']; ?> </p>
</div>
