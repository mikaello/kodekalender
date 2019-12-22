# The A-maze-ing Race

Av: Sverre Johann Bjørke

Til jul har Arthur og Isaac fått kvar sin robot som kan programmerast til å
løyse labyrintar. Dei programerar inn to ganske like strategiar, og set robotane
til å løyse [denne labyrinten](maze.txt.zip) på 500x500 rom. Begge startar i rom
(0,0), og målet er i rom (499, 499)

Arthur har følgande strategi:

- Roboten prioriterar alltid ubesøkte rom før besøkte.
- Roboten prioriterar ubesøkte rom i denne rekkefølga: nedover, høgre, venstre,
  oppover.
- Om det er ingen ubesøkte rom å gå til, går roboten tilbake til forrige rom.

Isaac programerar sin identisk, bortsett frå at roboten hans prioriterar å
besøke nye rom i rekkefølga høgre, nedover, venstre, oppover

Eit enkelt rom i labyrinten har følgande eigenskapar:

- x - x-posisjon i labyrinten
- y - y-posisjon i labyrinten
- top - `true` om romet er stengt av ein vegg i retning oppover. `false` om det
  er passasje til tilstøytande rom.
- left - `true` om romet er stengt av ein vegg i retning venstre. `false` om det
  er passasje til tilstøytande rom.
- bottom - `true` om romet er stengt av ein vegg i retning nedover. `false` om
  det er passasje til tilstøytande rom.
- right - `true` om romet er stengt av ein vegg i retning høgre. `false` om det
  er passasje til tilstøytande rom.

# Spørsmål

Kor mange færre rom besøkte vinnarroboten?
