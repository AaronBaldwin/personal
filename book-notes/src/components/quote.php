<?php
function printQuote($speaker, $text) {
  echo "<div class='quote'>
    <p class='speaker'>$speaker</p>
    <span class='quotemark top'>“</span>
    <p class='text'>$text</p>
    <span class='quotemark bottom'>„</span>
  </div>";
}
?>
