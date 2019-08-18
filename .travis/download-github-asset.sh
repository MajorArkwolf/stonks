read owner repo tag name <<<$@

GITHUB_API="https://api.github.com"
GITHUB_REPO="$GITHUB_API/repos/$owner/$repo"
GITHUB_TAGS="$GITHUB_REPO/releases/tags/$tag"
AUTH="Authorization: token $GITHUB_TOKEN"
WGET_ARGS="--content-disposition --auth-no-challenge --no-cookie"
CURL_ARGS="-LJO#"

# Read asset tags.
response=$(curl -sH "$AUTH" $GITHUB_TAGS)
# Get ID of the asset based on given name.
eval $(echo "$response" | grep -C3 "name.:.\+$name" | grep -w id | tr : = | tr -cd '[[:alnum:]]=')
GITHUB_ASSET="$GITHUB_REPO/releases/assets/$id"

# Download asset.
curl $CURL_ARGS -H 'Accept: application/octet-stream' "$GITHUB_ASSET?access_token=$GITHUB_TOKEN"
